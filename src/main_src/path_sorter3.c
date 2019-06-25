/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_sorter3.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/25 12:39:15 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/25 15:01:52 by ocrossi     ###    #+. /#+    ###.fr     */
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
	FPF("end of bruteforce \n");
	print_tab(&res, max_paths);
	size_tab = check_path_found(&res, max_paths, data->path_nbr);
	FPF("yo check_path_found res %u\n", size_tab);
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
//		FPF("i = %u size small tabs = %u index = %u\n", i, size_small_tabs, index);
		if (!(data->ret[i] = (UINT*)malloc(sizeof(UINT) * (size_small_tabs + 1))))
		{
			f_error(ERR_MALLOC, NULL);
			return ;
		}
		data->ret[i][0] = size_small_tabs + 1;
		swap_tab_to_res(&(data->ret[i]), &res, data, index);
		i++;
	}
	print_final_path_tab(data);
}