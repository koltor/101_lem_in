/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_prepare_get_nodes.c             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 18:09:19 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/25 13:58:25 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

static void	*thread_main(void *arg)
{
	t_thread	thread;

	thread = *(t_thread*)arg;
	if (thread.id == NB_THREAD)
		get_nodes_thread_main(thread.data, (thread.id - 1) * thread.section,
		thread.data->rooms, thread.data->rooms);
	else
	{
		get_nodes_thread_main(thread.data, (thread.id - 1) * thread.section,
		thread.id * thread.section, thread.data->rooms);
	}
	return (NULL);
}

static void	prepare_thread(t_thread (*thread)[NB_THREAD], t_data *data)
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
		(*thread)[i].file_line = NULL;
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

t_bool		multithreading_get_nodes(t_data *data)
{
	t_thread thread[NB_THREAD];

	if (multithread_malloc_nodes(data))
		return (false);
	prepare_thread(&thread, data);
	launch_thread(&thread, data);
	wait_thread(&thread, data);
	return (true);
}
