/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/17 14:13:39 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 18:31:50 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	swap_current_tab(UINT *ctab, UINT i, t_data *data)
{
	UINT j;
	UINT id_room;

	j = data->paths[i][1] - 1;
	data->paths[i][j] = 1;
	j--;
	id_room = 1;
	while (j >= 3)
	{
		id_room = fill_tabs_with_current_room2(i, id_room, data, j);
		j--;
	}
}

UINT	compare_both_tabs(UINT *ctab, UINT *ptab)
{
	UINT i;

	i = 3;
	while (i < ctab[1])
	{
		if (ctab[i] != ptab[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}

UINT	compare_current_tab_with_prev(UINT *ctab, UINT **list_tabs,
				UINT index)
{
	UINT i;

	i = 0;
	while (i < index)
	{
		if (ctab[1] == list_tabs[i][1] && compare_both_tabs(ctab,
								list_tabs[i]) == 1)
			return (1);
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
		while (j >= 3)
		{
			id_room = fill_tabs_with_current_room(i, id_room, data, j);
			j--;
		}
		if (i >= 1 && compare_current_tab_with_prev(data->paths[i],
					data->paths, i))
			swap_current_tab(data->paths[i], i, data);
		i++;
	}
}
