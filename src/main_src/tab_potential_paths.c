/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_potential_paths.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/18 16:34:24 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 18:21:21 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	fill_ret_tab_norm(t_data *data, UINT (*id_tab)[], UINT index, UINT j)
{
	data->ret[index][(*id_tab)[j]]++;
	(*id_tab)[data->npath]--;
}

UINT	get_bit_place(ULL path_list)
{
	ULL		max;
	UINT	cpt;

	max = 0x4000000000000000;
	cpt = 63;
	while (max != path_list)
	{
		max = max / 2;
		cpt--;
	}
	return (cpt);
}

UINT	find_pname(ULL *path_id, UINT nb_link_tubes_start)
{
	UINT path_name;

	path_name = 0;
	while (nb_link_tubes_start)
	{
		if ((*path_id & bin(nb_link_tubes_start)))
		{
			*path_id -= bin(nb_link_tubes_start);
			path_name = get_bit_place(bin(nb_link_tubes_start));
			break ;
		}
		nb_link_tubes_start--;
	}
	return (path_name);
}

UINT	count_bits(t_tube tube)
{
	ULL		path_cp;
	UINT	cpt;

	cpt = 0;
	path_cp = tube.path_id;
	while (path_cp)
	{
		cpt += path_cp & 1;
		path_cp >>= 1;
	}
	return (cpt);
}

UINT	potential_path_counter(t_data *data)
{
	UINT i;
	UINT ret;

	i = 0;
	ret = 0;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		ret = ret + count_bits(data->t_tab[data->r_tab[1].link_tubes[i]]);
		i++;
	}
	return (ret);
}
