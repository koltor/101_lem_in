/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_ppaths_opti.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/22 10:39:09 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/24 14:12:43 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	set_tabs_with_order(t_data *data, UINT (*tab)[], UINT (*rtab)[], UINT index)
{
	UINT i;
	UINT size;

	i = 0;
	size = data->ret[index][data->pp + 1];
	while (i < size)
	{
		(*tab)[i] = get_smallest_path(data, index);
		data->ret[index][(*tab)[i]] = data->paths[(*tab)[i]][1] - 5;
		//(*rtab)[i] = data->paths[(*tab)[i]][1] - 4;
		i++;
	}
//	FPF("end of set tab with order\n");
//	print_tab2(data, tab, size);
}


void	cp_ret_tab(t_data *data, UINT (*rtab)[])
{
	UINT i;

	i = 0;
	while (i < data->pp)
	{
		data->ret[(*rtab)[data->pp + 1]][i] = (*rtab)[i];
		i++;
	}
}

UINT	get_size_first_usable_elem(t_data *data, UINT (*rtab)[])
{
	UINT i;

	i = 0;
	while (i < data->pp)
	{
		if ((*rtab)[i] != 0)
			return ((*rtab)[i] + (data->paths[i][1] - 5));
		i++;
	}
	return (0);
}

UINT 	detect_biggest_lap(t_data *data, UINT (*rtab)[]) // on en est la jpp go ff sa mere
{
	UINT i;
	UINT index;
	UINT ret;

	i = 0;
	index = 0;
	ret = get_size_first_usable_elem(data, rtab);
	FPF("debut ret = %u\n", ret);
	print_tab(rtab, data->pp);
	while (i < data->pp)
	{
		if ((*rtab)[i] != 0 && ret < ((*rtab)[i] + (data->paths[i][1] - 5)))
		{
			FPF("dans le traitement ret %u\n", ret);
			ret = ((*rtab)[i] + (data->paths[i][1] - 5));
			index = i;
		}
		i++;
	}
	FPF("\n||end of biggest lap ret = %u||\n", ret);
	FPF("INDICE DU TAB DE RET %u\n", (*rtab)[data->pp + 1]);
	return (ret);
}

UINT	substract_len_paths(t_data *data, UINT (*id_tab)[], UINT (*rtab)[], UINT index)
{
	UINT i;
	UINT size;
	UINT ret;
	UINT x;

	i = 0;
	size = (*rtab)[data->pp + 2];
	while (i < size)
	{
		(*rtab)[(*id_tab)[i]] = (*rtab)[(*id_tab)[i]] - (data->paths[(*id_tab)[i]][1] - 5);
	//	FPF("la putaind e ta race substarct len path i = %u res = %u\n", i, (*rtab)[(*id_tab)[i]]);
		i++;
	}
	cp_ret_tab(data, rtab);
	ret = detect_biggest_lap(data, rtab);
	return (ret);
}

t_bool	divide_ants_on_shortest_paths(t_data *data, UINT (*id_tab)[],
		UINT (*rtab)[], UINT i)
{
	UINT j;
	t_bool test;

	j = 0;
	test = false;
	while ((*rtab)[(*id_tab)[j]] != (*rtab)[(*id_tab)[i]])
	{
	//	FPF("debut i = %u j = %u\n", i, j);
		if (j == i - 1 && (*rtab)[(*id_tab)[0]] <= (*rtab)[(*id_tab)[j]])
			j = 0;
		if ((*rtab)[data->pp] == 0)
		{
			print_res_tab(data, rtab, id_tab, (*rtab)[data->pp + 2]);
			return (true);
		}
		(*rtab)[(*id_tab)[j]]++;
		(*rtab)[data->pp]--;
		j++;
	//	FPF("fin i = %u j = %u tamer le max %u\n", i, j, (*rtab)[data->pp + 2]);
		if (i == j && i == (*rtab)[data->pp + 2])
			return (false);
	}
	
	return (true);
}

UINT	get_place_in_rtab(t_data *data, UINT (*rtab)[], UINT (*id_tab)[])
{
	UINT i;

	i = 0;
	while (i < (*rtab)[data->pp + 2])
	{
		FPF("dans get place in rtab i = %u\n", i);
		if (i > 0 && (*rtab)[(*id_tab)[i]] < (*rtab)[(*id_tab)[i - 1]])
			return (i);
		i++;
	}
	return (0);
}

UINT gtamer = 0;

void	special_case_filler(t_data *data, UINT (*rtab)[], UINT (*id_tab)[])
{
	UINT i;

	FPF("\nspecial case filler start\n");
	print_res_tab(data, rtab, id_tab, (*rtab)[data->pp + 2]);
//	print_tab2(data, rtab, ((*rtab)[data->pp + 2] - 1));

	FPF("--------------------------------------------------------\n");
	i = get_place_in_rtab(data, rtab, id_tab);
	FPF("en of get place in rtab i = %u\n", i);
	while ((*rtab)[data->pp])
	{
		FPF("passage num %u\n", ++gtamer);
		while (i < (*rtab)[data->pp + 2])
		{
			if (i > 0 && ((*rtab)[(*id_tab)[i]] != ((*rtab)[(*id_tab)[i - 1]] - 1)))
				break ;
			if ((*rtab)[data->pp] == 0)
			{
				gtamer = 0;
				return ;
			}
			(*rtab)[(*id_tab)[i]]++;
			(*rtab)[data->pp]--;
			i++;
		}
		i = 0;
	}
}

UINT	set_result(t_data *data, UINT index)
{
	UINT	i;
	UINT	id_tab[data->ret[index][data->pp + 1]];
	UINT	rtab[data->pp + 3];

	i = 1;
	reset_marker_values(data);
	set_tab_zero(&rtab, data->pp + 1);
	rtab[data->pp] = data->ants;
	rtab[data->pp + 1] = index;
	rtab[data->pp + 2] = data->ret[index][data->pp + 1];
	set_tabs_with_order(data, &id_tab, &rtab, index);
	while (rtab[data->pp])
	{
		if (i >= rtab[data->pp + 2])
		{
			special_case_filler(data, &rtab, &id_tab);
			break ;
		}
		divide_ants_on_shortest_paths(data, &id_tab, &rtab, i);
		i++;
	}
	return (substract_len_paths(data, &id_tab, &rtab, index));
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
		FPF("dans sort opti i = %u\n", i);
		if (data->ret[i][data->pp + 1] == 0)
			break ;
		FPF("nb de chemins trouves pour le tab actuel = %u\n", data->ret[i][data->pp + 1]);
		data->ret[i][data->pp] = set_result(data, i);
	
		FPF("\nres en lap = %u du set_result d indice %u\n", data->ret[i][data->pp], i);

	//	ant_counter_checker(data, i);
		i++;
		FPF("________________________________________________\n");
		FPF("________________________________________________\n");
		FPF("________________________________________________\n");
	}
	print_cp_tab_binary(data);
	return (true);
}
