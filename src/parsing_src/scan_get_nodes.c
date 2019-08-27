/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_get_nodes.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/28 19:17:03 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 13:28:52 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** exit_get_node_malloc_error:
**	the function get and free the tab link_tubes in the different_room already
**	malloc in case of error
**	parameters
**		need the struct data
**		need the number of nodes already malloc
*/

static void	exit_get_node_malloc_error(t_data *data, UINT size)
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

static UINT	malloc_link_tubes(t_room *r_tab, UINT rooms)
{
	UINT i;

	i = 0;
	while (i < rooms)
	{
		if (!(r_tab[i].link_tubes = (UINT *)malloc(sizeof(UINT) *
											r_tab[i].nb_link_tubes)))
			return (*(UINT*)f_error(ERR_MALLOC, &i));
		r_tab[i].nb_link_tubes = 0;
		i++;
	}
	return (0);
}

/*
** malloc_link_tubes:
**	the function get and fill the tab link_tubes in the different_room
**	with the help of the struct tubes
**	parameters
**		need the struct data
**	return value
**		0 if all right
**		the number of nodes already malloc otherwise
*/

static void	detect_tubes(t_data *data, UINT id_tube)
{
	t_tube	*t_tab;
	t_room	*r_tab1;
	t_room	*r_tab2;

	t_tab = data->t_tab;
	r_tab1 = &data->r_tab[t_tab[id_tube].salle1];
	r_tab2 = &data->r_tab[t_tab[id_tube].salle2];
	r_tab1->link_tubes[r_tab1->nb_link_tubes++] = id_tube;
	r_tab2->link_tubes[r_tab2->nb_link_tubes++] = id_tube;
}

/*
** get_nodes:
**	the function get and fill the tab link_tubes in the different_room
**	this fill is call a node
**	parameters
**		need the struct data
**	return value
**		true if all right
**		false otherwise
*/

t_bool		get_nodes(t_data *data)
{
	UINT id_tubes;
	UINT ret;

	id_tubes = 0;
	if ((ret = malloc_link_tubes(data->r_tab, data->rooms)))
	{
		exit_get_node_malloc_error(data, ret + 1);
		return (false);
	}
	while (id_tubes < data->tubes)
		detect_tubes(data, id_tubes++);
	return (true);
}
