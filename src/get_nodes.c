/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_nodes.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/28 19:17:03 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/04 19:43:16 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	exit_get_node_malloc_error(t_data *data, UINT size)
{
	UINT cp_room;

	cp_room = data->rooms;
	while (size--)
		free(data->r_tab[size].link_tubes);
}

static UINT	malloc_link_tubes(t_data *data)
{
	UINT cp_room;
	UINT i;

	i = 0;
	cp_room = data->rooms;
	while (cp_room)
	{
		if (!(data->r_tab[i].link_tubes = (UINT *)malloc(sizeof(UINT) *
											data->r_tab[i].nb_link_tubes)))
			return (*(UINT*)f_error(ERR_MALLOC, &i));
		i++;
		cp_room--;
	}
	return (0);
}

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

void		get_nodes(t_data *data)
{
	UINT cp_room;
	UINT id_room;
	UINT ret;

	id_room = 0;
	cp_room = data->rooms;
	if ((ret = malloc_link_tubes(data)))
	{
		exit_get_node_malloc_error(data, ret + 1);
		return ;
	}
	while (cp_room)
	{
		detect_tubes(&data->r_tab[id_room], data, id_room);
		id_room++;
		cp_room--;
	}
}
