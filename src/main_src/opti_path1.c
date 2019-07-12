/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opti_path1.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 13:22:56 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/11 18:28:02 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	get_smallest_tab2(UINT (*res)[], UINT (*tabc)[], t_data *data,
		UINT *ret)
{
	UINT i;
	UINT index;

	i = 0;
	while (i < data->max_paths)
	{
		if ((*tabc)[i] < 1 && (*res)[i] != data->path_nbr)
		{
			*ret = data->paths[(*res)[i]][1];
			index = i;
			data->test = true;
			break ;
		}
		i++;
	}
	return (index);
}

UINT	get_smallest_tab(UINT (*res)[], UINT (*tabc)[], t_data *data,
		UINT max_paths)
{
	UINT	i;
	UINT	ret;
	UINT	index;

	
//	print_tab(res, max_paths);
//	print_tab(tabc, max_paths);
	data->test = false;
	i = 0;
	ret = 0;
	index = get_smallest_tab2(res, tabc, data, &ret);
//	FPF("index xmallest tab %u\n", index);
//	FPF("smallest tab\n");
//	print_one_potential_path(data, index);
//	print_potential_paths(data);
//	FPF("max path = %u\n", max_paths);
//	print_tab(res, max_paths);
//	print_tab(tabc, max_paths);
	while (i < max_paths)
	{
//		FPF("i = %u\n", i);
//		FPF("la merde qui me fait sgf %u\n", (*res)[i]);
//		print_one_potential_path(data, (*res)[i]);
//		FPF("la merde qui me fait sgf %u\n", data->paths[(*res)[i]][1]);
		if ((*tabc)[i] < 1 && (*res)[i] != data->path_nbr && ret >= data->paths[(*res)[i]][1])
		{
//			FPF("yo\n");
			ret = data->paths[(*res)[i]][1];
			index = i;
			data->test = true;
		}
		i++;
	}
	if (data->test == false)
		return (data->path_nbr);
	return (index);
}
