/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_ppaths_opti.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/22 10:39:09 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/22 20:19:27 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	set_tabs_with_order(t_data *data, UINT (*tab)[], UINT (*rtab)[],
		UINT index)
{
	UINT i;
	UINT size;

	i = 0;
	size = data->ret[index][data->pp + 1];
	while (i < size)
	{
		(*tab)[i] = get_smallest_path(data, index);
		(*rtab)[(*tab)[i]] = data->paths[(*tab)[i]][1] - 4;
		//(*rtab)[i] = data->paths[(*tab)[i]][1] - 4;
		i++;
	}
	FPF("end of set tab with order\n");
	print_tab2(data, tab, size);
}

void	substract_len_paths(t_data *data, UINT (*tab)[], UINT (*rtab)[], UINT index)
{
	UINT i;
	UINT size;

	i = 0;
	size = data->ret[index][data->pp + 1];
	while (i < size)
	{
		if ((*rtab)[(*tab)[i]] != data->paths[(*tab)[i]][1] - 4)
		{
			FPF("value |%u|                  value to sub %u path number %u\n", (*rtab)[(*tab)[i]], data->paths[(*tab)[i]][1] - 4, (*tab)[i]);
	//		(*rtab)[(*tab)[i]] -= data->paths[(*tab)[i]][1] - 3;
		}
	//	else
			(*rtab)[(*tab)[i]] -= data->paths[(*tab)[i]][1] - 4;
		i++;
	}
}

UINT	change_i_value(t_data *data, UINT (*tab)[], UINT (*rtab)[], UINT i)
{
	UINT ref;

	ref = i;
	while (i < data->pp)
	{
		if ((*rtab)[(*tab)[i]] > (*rtab)[(*tab)[ref]])
		{
			i--;
			break ;
		}
		i++;
	}
	return (i);
}

void	divide_ants_on_shortest_paths(t_data *data, UINT (*tab)[],
		UINT (*rtab)[], UINT i)
{
	UINT j;
	t_bool test;

	j = 0;
	test = false;
	while (j < i)
	{
		if ((*rtab)[(*tab)[j]] == ((*rtab)[(*tab)[i]] - 1) && j == i) // ! segf
		{
			FPF("break boucle [2] ants = %u j = %u j + 1 = %u res 1 = %u res 2 = %u\n", (*rtab)[data->pp], j, j + 1, (*rtab)[(*tab)[j]], (*rtab)[(*tab)[j + 1]]);
			break ;
		}
		if ((*rtab)[data->pp] == 0)
		{
			return ;
		}
		(*rtab)[(*tab)[j]]++;
		(*rtab)[data->pp]--;
		j++;
		FPF("allo rtab index %u rtab index + 1 %u i = %u j = %u\n", (*rtab)[(*tab)[j]], (*rtab)[(*tab)[j + 1]], i, j);
	}
	FPF("end of divide ants on shortest paths fourmis restantes = %u\n", (*rtab)[data->pp]);
	print_res_tab(data, rtab, tab, data->ret[(*rtab)[data->pp + 1]][data->pp + 1]);
}

UINT	set_result(t_data *data, UINT index)
{
	UINT i;
	UINT tab[data->ret[index][data->pp + 1]];
	UINT rtab[data->pp + 2]; // ou la case d indice data->pp == lap

	i = 1;
	reset_marker_values(data);
	set_tab_zero(&rtab, data->pp + 1);
	rtab[data->pp] = data->ants;
	rtab[data->pp + 1] = index;
	set_tabs_with_order(data, &tab, &rtab, index);
	while (1)
	{
//		if (i == 2)
//			break ;
		if (rtab[data->pp] == 0)
			break ;
		divide_ants_on_shortest_paths(data, &tab, &rtab, i);
		// penser au cas ou on utilise tt les paths
		i++;
	}
	FPF("wesh les fourmis ca se passe comment %u\n", rtab[data->pp]);
	substract_len_paths(data, &tab, &rtab, index);
	FPF("end of treatment\n");
	print_tab(&rtab, data->pp);
	//print_tab2(data, &rtab, data->pp);
	//return (rtab[data->pp]);
	return (1);
}

t_bool	sort_opti(t_data *data)
{
	UINT i;

	i = 0;
	if (data->pp == 1)
	{
		FPF("need for a special case function \n");
		return (false);
	}
	while (i < data->pp)
	{
		if (data->ret[i][data->pp + 1] == 0)
			break ;
		FPF("nb de chemins trouves pour le tab actuel = %u\n", data->ret[i][data->pp + 1]);
		data->ret[i][data->pp] = set_result(data, i);
		i++;
	}
	return (true);
}
