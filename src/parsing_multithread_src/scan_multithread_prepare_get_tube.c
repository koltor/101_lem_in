/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_prepare_get_tube.c              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 16:13:09 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 18:20:43 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

static void	*thread_main(void *arg)
{
	t_thread	thread;
	char		    *line;
	UINT		    stop;
	int			    type;

	thread = *(t_thread*)arg;
	//dprintf(1, "%u | DEPART thread\n",thread.id);
	scan_line_line_for_threading(NULL, thread.id - 1);
	skip_ants_number_for_threading(thread.file_line, thread.id - 1);
    line = skip_room_for_multithreading(thread.file_line, thread.id - 1);
	stop = (thread.id - 1) * thread.section;
   // dprintf(1, "%s\n", line);
	//dprintf(1, "%u | Nombre de tube a passer %u\n", thread.id, stop);
 	while (stop && line)
	{
		if ((type = is_tube(line)) == -1)
		{
	//		dprintf(1, "ARRET thread:%u | %u\n", thread.id, stop);
			return (NULL);
		}
		else if (type == 0)
				stop--;
    	line = scan_line_line_for_threading(thread.file_line, thread.id - 1);
	}
    if (!line)
    {
      //  dprintf(1, "ARRET thread:%u | %u\n", thread.id, stop);
		return (NULL);
    }
    //dprintf(1, "%s\n", line);
	get_tube_thread_main(thread.file_line, thread.data, thread, line);
	return (NULL);
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
		if ((*thread)[i].file_line)
        {
            free ((*thread)[i].file_line);
            (*thread)[i].file_line = NULL;
        }
		//dprintf(1,"%u | J'ai attendu\n", (*thread)[i].id);
		i++;
	}
}

static void	prepare_thread(t_thread (*thread)[NB_THREAD], t_data *data, char *file_line)
{
	UINT	i;
	float	sec;

	i = 0;
	sec = (float)data->tubes / (float)NB_THREAD;
	if (sec - (int)sec >= 0.5)
		sec += 0.5;
	if (sec < 1.0F)
		sec = 1.0F;
//	dprintf(1,"nb_tube: %u | initialisation des threads\n", data->tubes);
	while (i < NB_THREAD && i < data->rooms)
	{
		(*thread)[i].data = data;
		(*thread)[i].id = i + 1;
		(*thread)[i].pth = NULL;
		(*thread)[i].section = (UINT)sec;
		(*thread)[i].file_line = ft_strdup(file_line);
//		dprintf(1,"%u | sec: %u J'ai initialisé\n", (*thread)[i].id, (*thread)[i].section);
		i++;
	}
}

void    multithread_get_tube(char *file_line, t_data *data)
{
    t_thread thread[NB_THREAD];

    prepare_thread(&thread, data, file_line);
	launch_thread(&thread, data);
	wait_thread(&thread, data);
	launch_check_tube_thread(&thread, data);
	wait_thread(&thread, data);
}