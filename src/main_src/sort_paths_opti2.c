/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_paths_opti2.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/01 16:17:43 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/01 17:25:54 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	get_smallest_path(t_data *data, UINT index)
{
	UINT size;
	UINT ret;
	UINT i;

	i = 0;
	size = data->ret[index][data->pp];
	ret = index;
	while (i < data->pp)
	{
	//	FPF("i = %u marker path %u index tab %u size %u\n", i, data->paths[i][2], index, size);
		if (data->ret[index][i] == 1 && size >= data->paths[i][1] - 4 && data->paths[i][2] != USED)
		{
			size = data->paths[i][1] - 4;
			ret = i;
		}
		i++;
	}
	data->paths[ret][2] = USED;
	return (ret);
}

void	set_tab_with_order(t_data *data, UINT (*tab)[], UINT index)
{
	UINT i;
	UINT size;

	i = 0;
	size = data->ret[index][data->pp + 1];
	while (i < size)
	{
		(*tab)[i] = get_smallest_path(data, index);
		data->ret[index][(*tab)[i]] = data->paths[(*tab)[i]][1] - 4;
		//(*rtab)[i] = data->paths[(*tab)[i]][1] - 4;
		i++;
	}
//	FPF("end of set tab with order\n");
//	print_tab2(data, tab, size);
//	print_cp_tab_binary(data);
}

UINT	set_ref(t_data *data,UINT (*id_tab)[], UINT index)
{
	UINT i;
	UINT res;
	UINT save;

	i = 0;
	save = 0;
	res = data->ret[index][(*id_tab)[0]];
	while (i < data->npath)
	{
		if (data->ret[index][(*id_tab)[i]] > res)
			return (i);
		i++;
	}
	return (i);
}

void	fill_all_paths(t_data *data, UINT (*id_tab)[], UINT index)
{
	UINT i;

//	print_cp_tab_binary(data);
	while ((*id_tab)[data->npath])
	{
		i = 0;
		while (i < data->npath)
		{
	//		FPF("bonjour fill all paths ants nb %u i = %u casr = %u\n", (*id_tab)[data->npath], i, data->ret[index][(*id_tab)[i]]);
			if ((*id_tab)[data->npath] == 0)
				break ;
			data->ret[index][(*id_tab)[i]]++;
			(*id_tab)[data->npath]--;
			i++;
		}
	}
}
t_bool	fill_ret_tab(t_data *data, UINT (*id_tab)[], UINT i, UINT index)// pb d overflow voir pour la fin du tab de i
{
	UINT j;

	if (i == data->npath && data->ret[index][(*id_tab)[i - 1]] == data->ret[index][(*id_tab)[0]])
	{
		fill_all_paths(data, id_tab, index);
		return (true);
	}
	while ((*id_tab)[data->npath])
	{
		j = 0;
		if (data->ret[index][(*id_tab)[i]] == data->ret[index][(*id_tab)[j]])
			return (false);
		while (j < i)
		{
			if (j == i - 1 && data->ret[index][(*id_tab)[i]] == data->ret[index][(*id_tab)[j]])
				return (false);
			if ((*id_tab)[data->npath] == 0)
				return (true);
			data->ret[index][(*id_tab)[j]]++;
			(*id_tab)[data->npath]--;
			j++;
		}
	}
	return (false);
}


UINT	get_biggest_turn(t_data *data, UINT (*id_tab)[],  UINT index)
{
	UINT i;
	UINT res;

	i = 0;
	res = data->ret[index][(*id_tab)[i]] + data->paths[(*id_tab)[i]][1] - 4;
	while (i < data->npath)
	{
		if (res < data->ret[index][(*id_tab)[i]])
			res = data->ret[index][(*id_tab)[i]] + data->paths[(*id_tab)[i]][1] - 4;
		i++;
	}
	return (res - 1);
}

void	substract_path_len(t_data *data, UINT (*id_tab)[], UINT index)
{
	UINT i;

	i = 0;
	while (i < data->npath)
	{
		data->ret[index][(*id_tab)[i]] -= data->paths[(*id_tab)[i]][1] - 4;
		i++;
	}
}

UINT	set_res(t_data *data, UINT index)
{
	UINT id_tab[data->ret[index][data->pp + 1] + 1];
	UINT i;
	UINT lap;

	data->npath = data->ret[index][data->pp + 1];
	id_tab[data->npath] = data->ants;
	reset_marker_values(data);
	set_tab_with_order(data, &id_tab, index);
	while (id_tab[data->npath])
	{
		i = set_ref(data,&id_tab, index);
		if (!fill_ret_tab(data, &id_tab, i, index))
			break ;
	}
	substract_path_len(data, &id_tab, index);
	lap = get_biggest_turn(data, &id_tab, index);
	return (lap);	
}

UINT	get_smallest_opt(t_data *data)
{
	UINT index;
	UINT i;
	UINT res;

	index = 0;
	i = 0;
	res = data->ret[index][data->pp];
	while (i < data->pp)
	{
		if (res > data->ret[i][data->pp])
		{
			res = data->ret[i][data->pp];
			index = i;
		}
		i++;
	}
	return (index);
}

void	print_smallest_opt(t_data *data)
{
	UINT idx;
	UINT i;
	UINT ret;

	i = 0;
	ret = 0;
	idx = get_smallest_opt(data);
	FPF("\n---------------------------\n");
	FPF("idx = %u\nants = %u\n", idx, data->ants);
	FPF("ret index %u nb de chemins trouves = %u taille du plus grand chemin trouve = %u\n", idx, data->ret[idx][data->pp + 1], data->ret[idx][data->pp]);
	while (i < data->pp)
	{
		FPF(" %u ", data->ret[idx][i]);
		i++;
	}
	FPF("\n---------------------------\n");
	i = 0;
	FPF("avec taille des chemins ca donne\n");
	while (i < data->pp)
	{
		if (data->ret[idx][i] != 0)
		{
			FPF(" %u ", data->ret[idx][i] + (data->paths[i][1] - 5));
			ret++;
		}
		else
			FPF(" 0 ");
		i++;
	}
	FPF("\n---------------------------\nnb de chemins utilises = %u\n", ret);
	
}


t_bool	 sort_opti2(t_data *data)
{
	UINT i;

	i = 0;
	if (data->pp == 1)
	{
		FPF("need special case function\n");
	}
	while (i < data->pp)
	{
		if (data->ret[i][data->pp + 1] == 0)
			break ;
		if (!(data->ret[i][data->pp] = set_res(data, i)))
			return (false);
		i++;
	}
//	print_cp_tab_binary(data);
	print_smallest_opt(data);
	return (true);
}
