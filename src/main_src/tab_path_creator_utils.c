/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path_creator_utils.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/24 17:15:08 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 17:57:09 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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
