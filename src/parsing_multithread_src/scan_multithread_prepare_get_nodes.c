/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_prepare_get_nodes.c             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 18:09:19 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 18:37:01 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

static void	*thread_main(void *arg)
{
	t_thread	thread;

	thread = *(t_thread*)arg;
	if (thread.id == NB_THREAD)
		get_nodes_thread_main(thread.data, (thread.id - 1 ) * thread.section, thread.data->rooms);
	else
		get_nodes_thread_main(thread.data, (thread.id - 1 ) * thread.section, thread.id * thread.section);
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
	//dprintf(1,"nb_room: %u | initialisation des threads\n", data->rooms);
	while (i < NB_THREAD && i < data->rooms)
	{
		(*thread)[i].data = data;
		(*thread)[i].id = i + 1;
		(*thread)[i].pth = NULL;
		(*thread)[i].section = (UINT)sec;
		(*thread)[i].file_line = NULL;
	//	dprintf(1,"%u | sec: %u J'ai initialisé\n", (*thread)[i].id, (*thread)[i].section);
		i++;
	}
}

static void	launch_thread(t_thread (*thread)[NB_THREAD], t_data *data)
{
	UINT i;

	i = 0;
//	dprintf(1,"lancement des threads\n");
	while (i < NB_THREAD && i < data->rooms)
	{
		pthread_create(&(*thread)[i].pth, NULL, thread_main, &(*thread)[i]);
		//dprintf(1,"%u | J'ai lancé\n", (*thread)[i].id);
		i++;
	}
}

static void	wait_thread(t_thread (*thread)[NB_THREAD], t_data *data)
{
	UINT i;

	i = 0;
//	dprintf(1,"attente des threads\n");
	while (i < NB_THREAD && i < data->rooms)
	{
		pthread_join((*thread)[i].pth, NULL);
		free ((*thread)[i].file_line);
		//dprintf(1,"%u | J'ai attendu\n", (*thread)[i].id);
		i++;
	}
}

t_bool  multithreading_get_nodes(t_data *data)
{
    t_thread thread[NB_THREAD];

	if (multithread_malloc_nodes(data))
		return (false);
	prepare_thread(&thread, data);
	launch_thread(&thread, data);
	wait_thread(&thread, data);
    return (true);
}