/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_sorter3.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/25 12:39:15 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 13:23:26 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	check_path_found(UINT (*curr)[], UINT max_paths, UINT path_nbr)
{
	UINT res;
	UINT i;

	res = 0;
	i = 0;
	while (i < max_paths)
	{
		if ((*curr)[i] < path_nbr)
			res++;
		i++;
	}
	return (res);
}

void	tab_cp(UINT (*curr)[], UINT (*res)[], UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		(*res)[i] = (*curr)[i];
		i++;
	}
}


void	swap_tab_to_res(UINT **rtab, UINT (*res)[], t_data *data, UINT index)
{
	UINT i;

	i = 1;
	while (i < (*rtab)[0])
	{
		(*rtab)[i] = data->paths[(*res)[index]][i + 3];
		i++;
	}
}
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
void	print_final_path_tab(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (data->ret[i])
	{
		j = 1;
		while (j < data->ret[i][0])
		{
			FPF("alle %s\n", data->r_tab[data->ret[i][j]].name);
			j++;
		}
		i++;
	}
	data->path_nbr = i; // ATTENTION A CHANGER QUAND J ENLEVERAI L AFFICHAGE
}

void	set_tab_for_bf(UINT (*res)[], UINT path_nbr, UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		(*res)[i] = path_nbr;
		i++;
	}
}

void	get_lap(t_data *data)
{
	if (data->ants % data->path_nbr == 0 ||
			data->ret[data->ants % data->path_nbr - 1][0] <
			data->ret[data->path_nbr - 1][0])
	{
		data->lap = data->ret[data->path_nbr - 1][0] - 2 + data->ants / data->path_nbr;
		return ;
	}
	data->lap = data->ret[data->path_nbr - 1][0] - 1 + data->ants / data->path_nbr; // normalemeent c bon car les precedents sont d une taille inf ou egale
}

void	get_result_for_path_managment(t_data *data, UINT max_paths)
{
	UINT res[max_paths];
	UINT size_tab;
	UINT i;
	UINT size_small_tabs;
	UINT index;

	i = 0;
	bruteforce_sorter(data, max_paths, &res);
	FPF("end of bruteforce sorter\n");
	print_tab(&res, max_paths);
	opti_paths(&res, max_paths, data);
	size_tab = check_path_found(&res, max_paths, data->path_nbr);
	if (!(data->ret = (UINT**)malloc(sizeof(UINT*) * (size_tab + 1))))
	{
		f_error(ERR_MALLOC, NULL);
		return ;
	}
	data->ret[size_tab] = NULL;
	while (i < size_tab)
	{
		index = get_index_valid_tab(data, &res, max_paths);
		size_small_tabs = get_size_valid_tab(data, &res, max_paths);
		if (!(data->ret[i] = (UINT*)malloc(sizeof(UINT) * (size_small_tabs + 1))))
		{
			f_error(ERR_MALLOC, NULL);
			return ;
		}
		data->ret[i][0] = size_small_tabs + 1;
		swap_tab_to_res(&(data->ret[i]), &res, data, index);
		i++;
	}
	data->path_nbr = size_tab;
	get_lap(data);
	FPF("nb de fourmis = %u lap = %u\n", data->ants, data->lap);
	print_final_path_tab(data);
}
