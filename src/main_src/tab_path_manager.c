/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path_manager.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/24 18:30:45 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 18:31:10 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	unset_tab_ppath(t_data *data, UINT index)
{
	UINT i;

	i = 4;
	data->paths[index][2] = USED;
	while (i < data->paths[index][1] - 1)
	{
		data->r_tab[data->paths[index][i]].used = false;
		i++;
	}
}

UINT	unset_path(t_data *data, UINT index, UINT i)
{
	while (i < data->pp)
	{
		if (i == index)
		{
			i++;
			continue ;
		}
		if (data->ret[index][i] == 1)
		{
			unset_tab_ppath(data, i);
			data->ret[index][i] = 0;
			return (i);
		}
		i++;
	}
	return (i);
}

UINT	smallest_output_possible(t_data *data, UINT index)
{
	UINT i;

	i = 0;
	while (i < data->pp)
	{
		if (data->ret[index][i] != 0 && i != index)
			return (0);
		i++;
	}
	return (1);
}

void	reset_marker_values(t_data *data)
{
	UINT i;

	i = 0;
	while (data->paths[i])
	{
		data->paths[i][2] = NUSED;
		i++;
	}
}

void	get_new_solution2(t_data *data, UINT index, UINT (*id_tab)[])
{
	UINT new_tab[data->pp];
	UINT i;

	i = 0;
	while (1)
	{
		if (!superposition_tab(data, index) ||
				smallest_output_possible(data, index))
		{
			reset_markers(data);
			reset_marker_values(data);
			return ;
		}
		else
		{
			i = unset_path(data, index, i);
			set_ppath_from_smallest(data, index, id_tab);
			i++;
		}
	}
}
