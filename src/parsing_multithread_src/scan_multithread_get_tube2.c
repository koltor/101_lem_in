/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_get_tube2.c                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 17:42:33 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 16:45:43 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

static void	multithread_check_duplicate_tube(t_tube *t_tab, UINT size,
													UINT start, UINT end)
{
	UINT	i;
	UINT	j;

	i = start;
	while (i < end)
	{
		j = i + 1;
		while (j < size)
		{
			if ((t_tab[i].salle1 == t_tab[j].salle1 &&
				t_tab[i].salle2 == t_tab[j].salle2) ||
				(t_tab[i].salle1 == t_tab[j].salle2 &&
				t_tab[i].salle2 == t_tab[j].salle1))
			{
				f_error(ERR_DUPL_TUBE, NULL);
				return ;
			}
			j += 1;
		}
		i += 1;
	}
}

static void	*thread_main(void *arg)
{
	t_thread	thread;
	char		*line;
	int			type;

	thread = *(t_thread*)arg;
	if (thread.id == NB_THREAD)
		multithread_check_duplicate_tube(thread.data->t_tab,
		thread.data->tubes, (thread.id - 1) * thread.section,
		thread.data->tubes);
	else
		multithread_check_duplicate_tube(thread.data->t_tab,
		thread.data->tubes, (thread.id - 1) * thread.section,
		thread.id * thread.section);
	return (NULL);
}

void		launch_check_tube_thread(t_thread (*thread)[NB_THREAD], t_data *dat)
{
	UINT i;

	i = 0;
	while (i < NB_THREAD && i < dat->rooms)
	{
		pthread_create(&(*thread)[i].pth, NULL, thread_main, &(*thread)[i]);
		i++;
	}
}
