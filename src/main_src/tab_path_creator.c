/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path_creator.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 18:50:31 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 17:57:20 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	init_index_path(t_data *data, UINT index)
{
	data->ret[index][index] = 1;
	data->ret[index][data->pp] = data->paths[index][1] - 4;
	data->ret[index][data->pp + 1] = 1;
	set_used_rooms(index, data);
}

void	set_ppath_from_smallest_norm(t_data *data, UINT index,
		UINT (*id_tab)[], UINT i)
{
	data->ret[index][(*id_tab)[i]] = 1;
	data->ret[index][data->pp + 1] = data->ret[index][data->pp + 1] + 1;
	set_used_rooms((*id_tab)[i], data);
}

UINT	set_ppath_from_smallest(t_data *data, UINT index, UINT (*id_tab)[])
{
	UINT i;

	i = 0;
	init_index_path(data, index);
	while (i < data->pp)
	{
		if ((*id_tab)[i] == index)
		{
			i++;
			continue ;
		}
		if (is_valid(data->paths[(*id_tab)[i]], data)
				&& data->paths[(*id_tab)[i]][2] == NUSED)
		{
			if (data->ret[index][data->pp] < data->paths[(*id_tab)[i]][1] - 4)
				data->ret[index][data->pp] = data->paths[(*id_tab)[i]][1] - 4;
			set_ppath_from_smallest_norm(data, index, id_tab, i);
		}
		else
			data->ret[index][(*id_tab)[i]] = 0;
		i++;
	}
	if (data->ret[index][data->pp + 1] == data->pp)
		return (1);
	return (0);
}

t_bool	fill_comp_tab(t_data *data)
{
	UINT i;
	UINT id_tab[data->pp];

	i = 0;
	set_id_tab(data, &id_tab);
	while (i < data->pp)
	{
		if (set_ppath_from_smallest(data, i, &id_tab))
			break ;
		if (i >= 1 && superposition_tab(data, i))
		{
			get_new_solution2(data, i, &id_tab);
		}
		reset_markers(data);
		i++;
	}
	return (true);
}

t_bool	init_stocker_tab(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	if (!(data->ret = (UINT **)malloc(sizeof(UINT *) * (data->pp + 1))))
	{
		f_error(ERR_MALLOC, NULL);
		return (false);
	}
	data->ret[data->pp] = NULL;
	while (i < data->pp)
	{
		if (!(data->ret[i] = (UINT *)malloc(sizeof(UINT) * (data->pp + 2))))
		{
			f_error(ERR_MALLOC, NULL);
			return (false);
		}
		data->ret[i][data->pp + 1] = 0;
		i++;
	}
	return (true);
}
