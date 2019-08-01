/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path_creator.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 18:50:31 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/01 20:16:28 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	get_shortest_path(t_data *data)
{
	UINT i;
	UINT ret;
	UINT size;

	i = 0;
	while (i < data->pp)
	{
		if (data->paths[i][2] == NUSED)
			break ;
		i++;
	}
	ret = i;
	size = data->paths[i][1];
	while (i < data->pp)
	{
		if (data->paths[i][1] < size && data->paths[i][2] == NUSED)
		{
			ret = i;
			size = data->paths[i][1];
		}
		i++;
	}
	data->paths[ret][2] = USED;
	return (ret);
}

void	set_id_tab(t_data *data, UINT (*id_tab)[])
{
	UINT i;

	i = 0;
	while (i < data->pp)
	{
		(*id_tab)[i] = get_shortest_path(data);
		i++;
	}
	reset_marker_values(data);
}

void	init_index_path(t_data *data, UINT index)
{
	data->ret[index][index] = 1;
	data->ret[index][data->pp] = data->paths[index][1] - 4;
	data->ret[index][data->pp + 1] = 1;
	set_used_rooms(index, data);
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
		if (is_valid(data->paths[(*id_tab)[i]], data) && data->paths[(*id_tab)[i]][2] == NUSED)
		{
			if (data->ret[index][data->pp] < data->paths[(*id_tab)[i]][1] - 4)
				data->ret[index][data->pp] = data->paths[(*id_tab)[i]][1] - 4;
			data->ret[index][(*id_tab)[i]] = 1;
			data->ret[index][data->pp + 1] = data->ret[index][data->pp + 1] + 1;
			set_used_rooms((*id_tab)[i], data);
		}
		else
			data->ret[index][(*id_tab)[i]] = 0;
		i++;
	}
	if (data->ret[index][data->pp + 1] == data->pp)
		return (1);
	return (0);
}

UINT	set_solution_for_ppath(t_data *data, UINT index)
{
	UINT i;

	i = 0;
	init_index_path(data, index);
	while (i < data->pp)
	{
		if (i == index)
		{
			i++;
			continue ;
		}
		if (is_valid(data->paths[i], data) && data->paths[i][2] == NUSED)
		{
			if (data->ret[index][data->pp] < data->paths[i][1] - 4)
				data->ret[index][data->pp] = data->paths[i][1] - 4;
			data->ret[index][i] = 1;
			data->ret[index][data->pp + 1] = data->ret[index][data->pp + 1] + 1;
			set_used_rooms(i, data);
		}
		else
			data->ret[index][i] = 0;
		i++;
	}
	if (data->ret[index][data->pp + 1] == data->pp)
		return (1);
	return (0);
}

UINT	comp_unit_tab(t_data *data, UINT i1, UINT i2)
{
	UINT i;

	i = 0;
	while (i < data->pp)
	{
		if (data->ret[i1][i] != data->ret[i2][i])
			return (0);
		i++;
	}
	return (1);
}

UINT	superposition_tab(t_data *data, UINT index)
{
	UINT i;

	i = 0;
	while (1)
	{
		if (i == index)
			break ;
		if (comp_unit_tab(data, i, index))
			return (1);
		i++;
	}
	return (0);
}

t_bool	fill_comp_tab(t_data *data)
{
	UINT i;
	UINT id_tab[data->pp];

	i = 0;
	set_id_tab(data, &id_tab);
//	print_tab2(data, &id_tab, data->pp);
	while (i < data->pp)
	{
//		if (set_solution_for_ppath(data, i))
		if (set_ppath_from_smallest(data, i, &id_tab))
		{
			FPF("all possible path found\n");
			break ;
		}
		if (i >= 1 && superposition_tab(data, i))
		{
//			get_new_solution(data, i);
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
	FPF("max paths = %u\n", data->max_paths);
	FPF("nb de pot paths %u\n", data->pp);
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
