/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opti_paths.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/28 13:05:39 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 13:17:22 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	set_tab_zero(UINT (*tabc)[], UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		(*tabc)[i] = 0;
		i++;
	}
}

UINT	get_smallest_tab(UINT (*res)[], UINT (*tabc)[], t_data *data, UINT max_paths)
{
	UINT i;
	UINT ret;
	UINT index;
	t_bool test;

	test = false;
	i = 0;
	ret = 0;
	while (i < max_paths)
	{
		if ((*tabc)[i] < 1 && (*res)[i] != data->path_nbr)
		{
			ret = data->paths[(*res)[i]][1];
			index = i;
			test = true;
			break ;
		}
		i++;
	}
	i = 0;
//	FPF("mid smallest tab max path %u\n", max_paths);
	while (i < max_paths)
	{
		if ((*tabc)[i] < 1 && (*res)[i] != data->path_nbr && ret > data->paths[(*res)[i]][1])
		{
			ret = data->paths[(*res)[i]][1];
			index = i;
			test = true;
		}
//		FPF("i = %u\n", i);
		i++;
	}
	if (test == false)
		return (data->path_nbr);
//	FPF("end of smallest tab index smallest tab %u\n", index);
	return (index);
}

void	set_tab_with_opti(UINT (*res)[], UINT (*tabc)[], UINT max_paths, UINT path_nbr)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		if ((*tabc)[i] == 0)
			(*res)[i] = path_nbr;
		i++;
	}
}

void	sort_tab_crescent_order(UINT (*res)[], UINT (*tabc)[], UINT max_paths, t_data *data)
{
	UINT tabc2[max_paths];
	UINT ret;
	UINT i;
	UINT j;

	set_tab_for_bf(&tabc2, data->path_nbr, max_paths);
	i = 0;
	j = 0;
	ret = 1;
	while (i < max_paths)
	{
		if ((*tabc)[i] == ret)
		{
			tabc2[j] = (*res)[i];
			j++;
			ret++;
			i = 0;
			continue ;
		}
		i++;
	}
	FPF("tamer\n");
	print_tab(&tabc2, max_paths);
	tab_cp(&tabc2, res, max_paths);
	FPF("res a la fin\n");
	print_tab(res, max_paths);
}

void	opti_paths(UINT (*res)[], UINT max_paths, t_data *data) // a revoir
{
	UINT tabc[max_paths];
	UINT index;
	UINT lap;
	UINT ret;

	UINT test = 0;

	ret = 1;
	set_tab_zero(&tabc, max_paths);
	index = get_smallest_tab(res, &tabc, data, max_paths);
	lap = data->ants / ret + data->paths[(*res)[index]][1] - 4;
	FPF("on 1st turn lap = %u size du chemin %u index = %u\n", lap, data->paths[(*res)[index]][1] - 4, index);
	tabc[index] = ret;
	while (ret < max_paths)
	{
		ret++;
		index = get_smallest_tab(res, &tabc, data, max_paths);
		FPF("apres get smallest tab index = %u\n", index);
		if (index == data->path_nbr)
		{
			FPF("why\n");
			break ;
		}
		if (data->ants / ret + data->paths[(*res)[index]][1] - 4 > lap)
		{
			lap = data->ants / ret + data->paths[(*res)[index]][1] - 4;
			break ;
		}
		lap = data->ants / ret + data->paths[(*res)[index]][1] - 4;
		tabc[index] = ret;
		FPF("on turn num lap = %u ret = %u index = %u\n", lap, ret, index);
	}
	FPF("wtf sortie de boucle tabc\n");
	print_tab(&tabc, max_paths);
	set_tab_with_opti(res, &tabc, max_paths, data->path_nbr);
	print_tab(res, max_paths);
	sort_tab_crescent_order(res, &tabc, max_paths, data);
	print_tab(res, max_paths);
}
