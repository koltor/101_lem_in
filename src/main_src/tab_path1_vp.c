/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path1_vp.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 13:57:12 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 18:34:34 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	fill_tabs_with_current_room(UINT id_tab, UINT id_room, t_data *data,
				UINT cell)
{
	UINT	i;
	UINT	j;
	UINT	qt;
	UINT	pname;
	ULL		path_id_cp;

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
			if ((data->paths[id_tab][0] == pname) && (cell ==
				data->t_tab[data->r_tab[id_room].link_tubes[i]].tmp_turn[pname
				- 1] + 2))
			{
				data->paths[id_tab][cell] =
					get_id_room(data->t_tab[data->r_tab[id_room].link_tubes[i]],
									id_room);
				break ;
			}
			j++;
		}
		i++;
	}
	return (data->paths[id_tab][cell]);
}

UINT	fill_tabs_with_current_room2(UINT id_tab, UINT id_room, t_data *data,
				UINT cell)
{
	UINT	i;
	UINT	j;
	UINT	qt;
	UINT	pname;
	ULL		path_id_cp;

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
			if ((data->paths[id_tab][0] == pname) && (cell ==
				data->t_tab[data->r_tab[id_room].link_tubes[i]].tmp_turn[pname
				- 1] + 2))
			{
				data->paths[id_tab][cell] =
				get_id_room(data->t_tab[data->r_tab[id_room].link_tubes[i]],
								id_room);
				return (data->paths[id_tab][cell]);
			}
			j++;
		}
		i++;
	}
	return (data->paths[id_tab][cell]);
}
