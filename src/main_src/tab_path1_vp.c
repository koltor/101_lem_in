/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path1_vp.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 13:57:12 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 17:04:53 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	initialize_vp(t_vp *vp)
{
	vp->i = 0;
	vp->j = 0;
	vp->qt = 0;
}

void	norm_ftabs(t_vp *vp, t_data *data, UINT id_room)
{
	vp->path_id_cp = data->t_tab[data->r_tab[id_room].link_tubes[vp->i]]
		.path_id;
	vp->qt = vp->qt + count_bits(data->t_tab[data->r_tab[id_room].
		link_tubes[vp->i]]);
}

UINT	fill_tabs_with_current_room(UINT id_tab, UINT id_room, t_data *data,
				UINT cell)
{
	t_vp	vp;

	initialize_vp(&vp);
	while (vp.i < data->r_tab[id_room].nb_link_tubes)
	{
		norm_ftabs(&vp, data, id_room);
		while (vp.j < vp.qt)
		{
			vp.pname = find_pname(&vp.path_id_cp,
					data->r_tab[0].nb_link_tubes);
			if ((data->paths[id_tab][0] == vp.pname) && (cell ==
			data->t_tab[data->r_tab[id_room].link_tubes[vp.i]].
			tmp_turn[vp.pname - 1] + 2))
			{
				data->paths[id_tab][cell] =
					get_id_room(data->t_tab[data->r_tab[id_room].
							link_tubes[vp.i]], id_room);
				break ;
			}
			vp.j++;
		}
		vp.i++;
	}
	return (data->paths[id_tab][cell]);
}

UINT	fill_tabs_with_current_room2(UINT id_tab, UINT id_room, t_data *data,
				UINT cell)
{
	t_vp	vp;

	initialize_vp(&vp);
	while (vp.i < data->r_tab[id_room].nb_link_tubes)
	{
		norm_ftabs(&vp, data, id_room);
		while (vp.j < vp.qt)
		{
			vp.pname = find_pname(&vp.path_id_cp,
					data->r_tab[0].nb_link_tubes);
			if ((data->paths[id_tab][0] == vp.pname) && (cell ==
				data->t_tab[data->r_tab[id_room].link_tubes[vp.i]]
				.tmp_turn[vp.pname - 1] + 2))
			{
				data->paths[id_tab][cell] =
				get_id_room(data->t_tab[data->r_tab[id_room].
						link_tubes[vp.i]], id_room);
				return (data->paths[id_tab][cell]);
			}
			vp.j++;
		}
		vp.i++;
	}
	return (data->paths[id_tab][cell]);
}
