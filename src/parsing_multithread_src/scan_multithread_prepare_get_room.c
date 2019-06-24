/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_prepare_get_room.c              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 19:26:49 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 16:51:51 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

static void	*thread_main(void *arg)
{
	t_thread	thread;
	char		*line;
	UINT		stop;
	int			order;
	int			type;

	thread = *(t_thread*)arg;
	scan_line_line_for_threading(NULL, thread.id - 1);
	skip_ants_number_for_threading(thread.file_line, thread.id - 1);
	order = 0;
	stop = (thread.id - 1) * thread.section;
	while (stop)
	{
		line = scan_line_line_for_threading(thread.file_line, thread.id - 1);
		if ((type = is_room(line)) == -1)
			return (NULL);
		if (type == 1 && order == 0 && (order = is_order(line)))
			continue ;
		if (type == 0)
			if (order == 0 && (order = 0))
				stop--;
	}
	get_room_thread_main(thread.file_line, thread.data, thread);
	return (NULL);
}

static void	prepare_thread(t_thread (*thread)[NB_THREAD], t_data *data,
							char *file_line, t_info_thread *thread_info)
{
	UINT	i;
	float	sec;

	i = 0;
	sec = (float)data->rooms / (float)NB_THREAD;
	if (sec - (int)sec >= 0.5)
		sec += 0.5;
	if (sec < 1.0F)
		sec = 1.0F;
	while (i < NB_THREAD && i < data->rooms)
	{
		(*thread)[i].data = data;
		(*thread)[i].id = i + 1;
		(*thread)[i].pth = NULL;
		(*thread)[i].section = (UINT)sec;
		(*thread)[i].file_line = ft_strdup(file_line);
		(*thread)[i].thread = thread_info;
		i++;
	}
}

static void	launch_thread(t_thread (*thread)[NB_THREAD], t_data *data)
{
	UINT i;

	i = 0;
	while (i < NB_THREAD && i < data->rooms)
	{
		pthread_create(&(*thread)[i].pth, NULL, thread_main, &(*thread)[i]);
		i++;
	}
}

static void	wait_thread(t_thread (*thread)[NB_THREAD], t_data *data)
{
	UINT i;

	i = 0;
	while (i < NB_THREAD && i < data->rooms)
	{
		pthread_join((*thread)[i].pth, NULL);
		free((*thread)[i].file_line);
		i++;
	}
}

t_bool		multithread_get_room(char *file_line, t_data *data,
										t_info_thread *thread_info)
{
	t_thread	thread[NB_THREAD];
	t_bool		value;

	value = false;
	prepare_thread(&thread, data, file_line, thread_info);
	launch_thread(&thread, data);
	wait_thread(&thread, data);
	if (data->r_tab[0].name == NULL)
		return (*(t_bool*)f_error(ERR_LACK_BEGIN, &value));
	else if (data->r_tab[1].name == NULL)
		return (*(t_bool*)f_error(ERR_LACK_END, &value));
	else if (thread_info->rooms != data->rooms)
	{
		data->rooms = thread_info->rooms;
		return (false);
	}
	return (true);
}
