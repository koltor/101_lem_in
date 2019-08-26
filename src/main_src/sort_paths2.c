/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_paths2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/24 17:59:42 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 18:19:46 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	get_biggest_turn(t_data *data, UINT (*id_tab)[], UINT index)
{
	UINT i;
	UINT res;

	i = 0;
	res = data->ret[index][(*id_tab)[i]] + data->paths[(*id_tab)[i]][1] - 4;
	while (i < data->npath)
	{
		if (res < data->ret[index][(*id_tab)[i]])
			res = data->ret[index][(*id_tab)[i]] +
				data->paths[(*id_tab)[i]][1] - 4;
		i++;
	}
	return (res - 1);
}

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
		if (data->ret[index][i] == 1 && size >= data->paths[i][1] - 4
				&& data->paths[i][2] != USED)
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
		i++;
	}
}

UINT	set_ref(t_data *data, UINT (*id_tab)[], UINT index)
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

	while ((*id_tab)[data->npath])
	{
		i = 0;
		while (i < data->npath)
		{
			if ((*id_tab)[data->npath] == 0)
				break ;
			data->ret[index][(*id_tab)[i]]++;
			(*id_tab)[data->npath]--;
			i++;
		}
	}
}
