/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_nodes.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/28 19:17:03 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/13 15:01:58 by matheme     ###    #+. /#+    ###.fr     */
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

static UINT	malloc_link_tubes(t_data *data)
{
	UINT i;

	i = 0;
	while (i < data->rooms)
	{
		if (!(data->r_tab[i].link_tubes = (UINT *)malloc(sizeof(UINT) *
											data->r_tab[i].nb_link_tubes)))
			return (*(UINT*)f_error(ERR_MALLOC, &i));
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

static void	detect_tubes(t_room *room, t_data *data, UINT id_room)
{
	UINT tcp;
	UINT id_tube;
	UINT j;

	id_tube = -1;
	j = 0;
	tcp = data->tubes + 1;
	while (--tcp)
	{
		id_tube++;
		if (data->t_tab[id_tube].salle1 == id_room)
		{
			room->link_tubes[j] = id_tube;
			j++;
			continue ;
		}
		if (data->t_tab[id_tube].salle2 == id_room)
		{
			room->link_tubes[j] = id_tube;
			j++;
		}
	}
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
	UINT id_room;
	UINT ret;

	id_room = 0;
	if ((ret = malloc_link_tubes(data)))
	{
		exit_get_node_malloc_error(data, ret + 1);
		return (false);
	}
	while (id_room < data->rooms)
	{
		detect_tubes(&data->r_tab[id_room], data, id_room);
		id_room++;
	}
	return (true);
}