/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_prepare_get_room.c              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 19:26:49 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 19:13:16 by matheme     ###    #+. /#+    ###.fr     */
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
	//dprintf(1, "%u | DEPART thread\n",thread.id);
	scan_line_line_for_threading(NULL, thread.id - 1);
	skip_ants_number_for_threading(thread.file_line, thread.id - 1);
	order = 0;
	stop = (thread.id - 1) * thread.section;
	//dprintf(1, "%u | Nombre de salle a passer %u\n", thread.id, stop);
 	while (stop)
	{
		line = scan_line_line_for_threading(thread.file_line, thread.id - 1);
		if ((type = is_room(line)) == -1)
		{
	//		dprintf(1, "ARRET thread:%u | %u\n", thread.id, stop);
			return (NULL);
		}
		if (type == 1 && order == 0 && (order = is_order(line)))
			continue ;
		else if (type == 0)
		{
			if (order == 0)
				stop--;
			order = 0;
		}
	}
	get_room_thread_main(thread.file_line, thread.data, thread.id, thread.section);
	return (NULL);
}

static void	prepare_thread(t_thread (*thread)[NB_THREAD], t_data *data, char *file_line)
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
		(*thread)[i].file_line = ft_strdup(file_line);
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

t_bool	multithread_get_room(char *file_line, t_data *data)
{
	t_thread	thread[NB_THREAD];
	t_bool		value;

//	dprintf(1, "section = %f\n", (float)data->rooms / (float)NB_THREAD);
	value = false;
	prepare_thread(&thread, data, file_line);
	launch_thread(&thread, data);
	wait_thread(&thread, data);
	if (data->r_tab[0].name == NULL)
		return (*(t_bool*)f_error(ERR_LACK_BEGIN, &value));
	else if (data->r_tab[1].name == NULL)
		return (*(t_bool*)f_error(ERR_LACK_END, &value));
	return (true);
}