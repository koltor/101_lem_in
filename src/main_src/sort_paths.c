/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_paths_opti2.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/01 16:17:43 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 18:25:52 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_bool	fill_ret_tab(t_data *data, UINT (*id_tab)[], UINT i, UINT index)
{
	UINT j;

	if (i == data->npath && data->ret[index][(*id_tab)[i - 1]] ==
			data->ret[index][(*id_tab)[0]])
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
			if (j == i - 1 && data->ret[index][(*id_tab)[i]]
					== data->ret[index][(*id_tab)[j]])
				return (false);
			if ((*id_tab)[data->npath] == 0)
				return (true);
			fill_ret_tab_norm(data, id_tab, index, j);
			j++;
		}
	}
	return (false);
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
		i = set_ref(data, &id_tab, index);
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
		if (res > data->ret[i][data->pp] && data->ret[i][data->pp + 1] != 0)
		{
			res = data->ret[i][data->pp];
			index = i;
		}
		i++;
	}
	return (index);
}

t_bool	sort_opti2(t_data *data)
{
	UINT i;

	i = 0;
	while (i < data->pp)
	{
		if (data->ret[i][data->pp + 1] == 0)
			break ;
		if (!(data->ret[i][data->pp] = set_res(data, i)))
			return (false);
		i++;
	}
	data->index = get_smallest_opt(data);
	data->lap = data->ret[data->index][data->pp];
	return (true);
}
