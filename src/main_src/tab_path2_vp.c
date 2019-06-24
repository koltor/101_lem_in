/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/17 14:13:39 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 20:24:08 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	fill_tabs_with_current_room(UINT id_tab, UINT id_room, t_data *data, UINT cell)
{
	UINT i;
	UINT j;
	UINT qt;
	UINT pname;
	ULL path_id_cp;

	i = 0;
	j = 0;
	qt = 0;
	while (i < data->r_tab[id_room].nb_link_tubes)
	{
		path_id_cp = data->t_tab[data->r_tab[id_room].link_tubes[i]].path_id;
		qt = qt + count_bits(data->t_tab[data->r_tab[id_room].link_tubes[i]]);
		while (j < qt)
		{
			pname = find_pname(&path_id_cp, data->r_tab[0].nb_link_tubes);
			if ((data->paths[id_tab][0] == pname) && (cell == data->t_tab[data->r_tab[id_room].link_tubes[i]].tmp_turn[pname - 1] + 1))
			{
				data->paths[id_tab][cell] = get_id_room(data->t_tab[data->r_tab[id_room].link_tubes[i]], id_room);
				break ;
			}
			j++;
		}
		i++;
	}
	return (data->paths[id_tab][cell]);
}

UINT	fill_tabs_with_current_room2(UINT id_tab, UINT id_room, t_data *data, UINT cell)
{
	UINT i;
	UINT j;
	UINT qt;
	UINT pname;
	ULL path_id_cp;

	i = 0;
	j = 0;
	qt = 0;
	while (i < data->r_tab[id_room].nb_link_tubes)
	{
		path_id_cp = data->t_tab[data->r_tab[id_room].link_tubes[i]].path_id;
		qt = qt + count_bits(data->t_tab[data->r_tab[id_room].link_tubes[i]]);
		while (j < qt)
		{
			pname = find_pname(&path_id_cp, data->r_tab[0].nb_link_tubes);
			if ((data->paths[id_tab][0] == pname) && (cell == data->t_tab[data->r_tab[id_room].link_tubes[i]].tmp_turn[pname - 1] + 1))
			{
				data->paths[id_tab][cell] = get_id_room(data->t_tab[data->r_tab[id_room].link_tubes[i]], id_room);
				return (data->paths[id_tab][cell]);
			}
			j++;
		}
		i++;
	}
	return (data->paths[id_tab][cell]);
}

void	swap_current_tab(UINT *ctab, UINT i, t_data *data)
{
	UINT j;
	UINT id_room;

	j = data->paths[i][1] - 1;
	data->paths[i][j] = 1;
	j--;
	id_room = 1;
	while (j >= 2)
	{
		id_room = fill_tabs_with_current_room2(i, id_room, data, j);
		j--;
	}
}


UINT	compare_both_tabs(UINT *ctab, UINT *ptab)
{
	UINT i;

	i = 2;
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

UINT	compare_current_tab_with_prev(UINT *ctab, UINT **list_tabs, UINT index)
{
	UINT i;

	i = 0;
	FPF("index %u\n", index);
	while (i < index)
	{
		FPF("i = %u\n", i);
		if (ctab[1] == list_tabs[i][1] && compare_both_tabs(ctab, list_tabs[i]) == 1)
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
		while (j >= 2)
		{
			id_room = fill_tabs_with_current_room(i, id_room, data, j);
			j--;
		}
		if (i >= 1 && compare_current_tab_with_prev(data->paths[i], data->paths, i))// a refaire au propre, ptit bug dans compare tab
		{
			FPF("suce\n");
			swap_current_tab(data->paths[i], i, data);
		}
		i++;
	}
	print_potential_paths(data);
}
