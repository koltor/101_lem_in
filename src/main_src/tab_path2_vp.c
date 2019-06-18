/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/17 14:13:39 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/17 17:59:40 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	fill_tabs_with_current_room(UINT id_tab, UINT id_room, t_data *data, UINT cell)
{
	UINT i;

	i = 0;
	while (i < data->r_tab[id_room].nb_link_tubes)
	{
		if ((data->paths[id_tab][0] ==
					data->t_tab[data->r_tab[id_room].link_tubes[i]].path_id) &&
				(cell == data->t_tab[data->r_tab[id_room].link_tubes[i]].turn + 1))
		{
			data->paths[id_tab][cell] = get_id_room(data->t_tab[data->r_tab[id_room].link_tubes[i]], id_room);
			break ;
		}
		i++;
	}
	return (data->paths[id_tab][cell]);
}

void	print_malloc_tab(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->paths[i] != NULL)
	{
		j = 2;
		while (j < data->paths[i][1])
		{
			printf("tab n* %d name room = %s\n", i, data->r_tab[data->paths[i][j]].name);
			j++;
		}
		i++;
	}
}

UINT	get_next_room(t_data *data, UINT path_id)
{
	UINT i;

	i = 0;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		if (data->t_tab[data->r_tab[1].link_tubes[i]].path_id == path_id)
			return (get_id_room(data->t_tab[data->r_tab[1].link_tubes[i]], 1));
		i++;
	}
	return (0);
}

void	fill_tabs_with_rooms(t_data *data)
{
	UINT id_room;
	UINT i;
	UINT j;

	i = 0;
	while (data->paths[i] != NULL)
	{
		j = data->paths[i][1] - 1;
		data->paths[i][j] = 1;
		j--;
		id_room = 1;
		while (j >= 2)
		{
			id_room = fill_tabs_with_current_room(i, id_room, data, j);
			j--;
		}
		i++;
	}
	print_malloc_tab(data);
}
