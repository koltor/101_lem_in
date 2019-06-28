/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_prepare_get_tube.c              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 16:13:09 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 18:03:04 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

static void	*thread_main(void *arg)
{
	t_thread	thread;
	char		*line;
	UINT		stop;
	int			type;

	thread = *(t_thread*)arg;
	scan_line_line_for_threading(NULL, thread.id - 1);
	skip_ants_number_for_threading(thread.file_line, thread.id - 1);
	line = skip_room_for_multithreading(thread.file_line, thread.id - 1);
	stop = (thread.id - 1) * thread.section;
	while (stop && line)
	{
		if ((type = is_tube(line)) == -1)
		{
			f_error(ERR_TUBES_FORMAT, NULL);
			return (NULL);
		}
		if (type == 0)
			stop--;
		line = scan_line_line_for_threading(thread.file_line, thread.id - 1);
	}
	if (!line)
		return (NULL);
	get_tube_thread_main(thread.file_line, thread.data, thread, line);
	return (NULL);
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
		if ((*thread)[i].file_line)
		{
			free((*thread)[i].file_line);
			(*thread)[i].file_line = NULL;
		}
		i++;
	}
}

static void	prepare_thread(t_thread (*thread)[NB_THREAD], t_data *data,
									char *file_line, t_info_thread *thread_info)
{
	UINT	i;
	float	sec;

	i = 0;
	sec = (float)data->tubes / (float)NB_THREAD;
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

void		multithread_get_tube(char *file_line, t_data *data,
										t_info_thread *thread_info)
{
	t_thread thread[NB_THREAD];

	prepare_thread(&thread, data, file_line, thread_info);
	launch_thread(&thread, data);
	wait_thread(&thread, data);
	data->tubes = thread_info->tubes;
	//launch_check_tube_thread(&thread, data);
	//wait_thread(&thread, data);
}
