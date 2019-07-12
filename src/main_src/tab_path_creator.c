/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path_creator.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 18:50:31 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/12 16:49:23 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	set_solution_for_ppath(t_data *data, UINT index)
{
	UINT i;

	i = 0;
	data->ret[index][index] = 1;
	data->ret[index][data->pp] = data->paths[index][1] - 3;
	data->ret[index][data->pp + 1] = 1;
	set_used_rooms(index, data);
	while (i < data->pp)
	{
		if (i == index)
		{
			i++;
			continue ;
		}
		if (is_valid(data->paths[i], data))
		{
			if (data->ret[index][data->pp] < data->paths[i][1] - 3)
				data->ret[index][data->pp] = data->paths[i][1] - 3;
			data->ret[index][i] = 1;
			data->ret[index][data->pp + 1]++;
			set_used_rooms(i, data);
		}
		else
			data->ret[index][i] = 0;
		i++;
	}
}

t_bool	fill_comp_tab(t_data *data)
{
	UINT i;

	i = 0;
	while (i < data->pp)
	{
		set_solution_for_ppath(data, i);
		// a rajouter la partie opti paths
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
		i++;
	}
	return (true);
}
