/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opti_paths.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/28 13:05:39 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/11 17:37:52 by ocrossi     ###    #+. /#+    ###.fr     */
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
	tab_cp(&tabc2, res, max_paths);
}

void	opti_paths(UINT (*res)[], UINT max_paths, t_data *data)
{
	UINT tabc[max_paths];
	UINT index;
	UINT lap;
	UINT ret;

	ret = 1;
	data->max_paths = max_paths;
	set_tab_zero(&tabc, max_paths);
	index = get_smallest_tab(res, &tabc, data, max_paths);
	lap = data->ants / ret + data->paths[(*res)[index]][1] - 4;
	tabc[index] = ret;
	while (ret < max_paths)
	{
		ret++;
		index = get_smallest_tab(res, &tabc, data, max_paths);
		if (index == data->path_nbr)
			break ;
		if (data->ants / ret + data->paths[(*res)[index]][1] - 4 > lap)
		{
			lap = data->ants / ret + data->paths[(*res)[index]][1] - 4;
			break ;
		}
		lap = data->ants / ret + data->paths[(*res)[index]][1] - 4;
		tabc[index] = ret;
	}
	set_tab_with_opti(res, &tabc, max_paths, data->path_nbr);
	sort_tab_crescent_order(res, &tabc, max_paths, data);
}
