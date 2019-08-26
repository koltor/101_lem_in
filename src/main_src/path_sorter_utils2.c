/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_sorter_utils2.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/26 17:25:01 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 17:47:25 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	set_tab_zero(UINT max_paths, UINT (*tabc)[])
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		(*tabc)[i] = 0;
		i++;
	}
}

UINT	count_id_paths(t_data data)
{
	UINT i;
	UINT ret;
	UINT cpid;
	UINT tab[4097];

	i = 0;
	ret = 0;
	cpid = 0;
	set_tab_zero(4097, &tab);
	while (data.paths[i])
	{
		if (data.paths[i][0] != 0 && tab[data.paths[i][0]] == 0)
		{
			tab[data.paths[i][0]]++;
			ret++;
		}
		i++;
	}
	return (ret);
}

UINT	is_valid(UINT *tab, t_data *data)
{
	UINT i;

	i = 4;
	while (i < tab[1] - 1)
	{
		if (data->r_tab[tab[i]].used == true)
			return (0);
		i++;
	}
	return (1);
}

UINT	max_paths(t_data data)
{
	UINT max_paths;

	if (data.r_tab[0].nb_link_tubes < data.r_tab[1].nb_link_tubes)
		max_paths = data.r_tab[0].nb_link_tubes;
	max_paths = data.r_tab[1].nb_link_tubes;
	if (count_id_paths(data) < max_paths)
		max_paths = count_id_paths(data);
	return (max_paths);
}
