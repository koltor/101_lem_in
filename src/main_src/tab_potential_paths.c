/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_potential_paths.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/18 16:34:24 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/18 19:51:22 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	count_bits(t_tube tube)
{
	ULL path_cp;
	UINT cpt;

	cpt = 0;
	path_cp = tube.path_id;
	while (path_cp)
	{
	//	ft_printf("path_cp %llu binaire = %b\n", path_cp, path_cp);
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
//		printf("ret %u\n", ret);
		ret = ret + count_bits(data->t_tab[data->r_tab[1].link_tubes[i]]);
		i++;
	}
	printf("ret fin %u\n", ret);
	return (ret);
}

void	print_number_paths(t_data *data)
{
	UINT i;

	i = 0;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		printf("dans tube n* %u compteur de chemins = %u\n", i, count_bits(data->t_tab[data->r_tab[1].link_tubes[i]]));
		i++;
	}
}

