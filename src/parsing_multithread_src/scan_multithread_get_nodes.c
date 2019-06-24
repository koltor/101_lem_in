/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_get_nodes.c                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 18:23:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 16:39:53 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

/*
** exit_get_node_malloc_error:
**	the function get and free the tab link_tubes in the different_room already
**	malloc in case of error
**	parameters
**		need the struct data
**		need the number of nodes already malloc
*/

static void		exit_get_node_malloc_error(t_data *data, UINT size)
{
	UINT cp_room;

	cp_room = data->rooms;
	while (size--)
		free(data->r_tab[size].link_tubes);
}

/*
** malloc_link_tubes:
**	the function get and prepare the tab link_tubes in the different_room
**	with malloc
**	parameters
**		need the struct data
**	return value
**		0 if all right
**		the number of nodes already malloc otherwise
*/

static UINT		malloc_link_tubes(t_room *r_tab, UINT rooms)
{
	UINT i;

	i = 0;
	while (i < rooms)
	{
		if (!(r_tab[i].link_tubes = (UINT *)malloc(sizeof(UINT) *
											r_tab[i].nb_link_tubes)))
			return (*(UINT*)f_error(ERR_MALLOC, &i));
		i++;
	}
	return (0);
}

t_bool			multithread_malloc_nodes(t_data *data)
{
	UINT ret;

	if ((ret = malloc_link_tubes(data->r_tab, data->rooms)))
	{
		exit_get_node_malloc_error(data, ret + 1);
		return (false);
	}
	return (true);
}

static void		multithread_detect_tubes(t_data *data, UINT id_room)
{
	UINT	id_tube;
	t_room	*room;
	t_tube	*t_tab;
	UINT	j;

	id_tube = 0;
	t_tab = data->t_tab;
	room = &data->r_tab[id_room];
	j = 0;
	while (j < room->nb_link_tubes)
	{
		if (t_tab[id_tube].salle1 == id_room ||
			t_tab[id_tube].salle2 == id_room)
			room->link_tubes[j++] = id_tube;
		id_tube++;
	}
}

void			get_nodes_thread_main(t_data *data, UINT start, UINT end)
{
	UINT id_room;

	id_room = start;
	while (id_room < end)
		multithread_detect_tubes(data, id_room++);
}
