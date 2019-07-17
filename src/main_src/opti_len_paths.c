/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opti_len_paths.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/16 13:05:25 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/17 20:45:54 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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
	//	FPF("i = %u marker path %u index tab %u size %u\n", i, data->paths[i][2], index, size);
		if (data->ret[index][i] == 1 && size >= data->paths[i][1] - 4 && data->paths[i][2] != USED)
		{
			size = data->paths[i][1] - 4;
			ret = i;
		}
		i++;
	}
	data->paths[ret][2] = USED;
	return (ret);
}

UINT	manage_lap_ovf(t_data *data, UINT i, UINT ids)
{
	UINT lap;

	FPF("on test le mod du lap : %u\n", data->ants % i);
	if ((data->ants % i))
		FPF("on test le mod du lap : %u\nles tailles des chemins a comparer : 1 %u | 2 %u\n", data->ants % i, data->paths[data->ants % i - 1][1], data->paths[ids][1]);
	if (data->ants % i != 0 && data->paths[data->ants % i - 1][1] == data->paths[ids][1])
	{
		lap = data->ants / i + data->paths[ids][1] - 3; 
		FPF("all l overflow lap = %u\n", lap);
	}
	else
	{
		lap = data->ants / i + data->paths[ids][1] - 4;
		FPF("cas normal lap = %u\n", lap);
	}
	return (lap);
}

UINT	set_opti_tab(t_data *data, UINT index)// pb de lap counter
{
	UINT i;
	UINT ids;
	UINT lap;

	i = 1;
	ids = get_smallest_path(data, index);
	lap = manage_lap_ovf(data, i, ids);
	data->ret[index][ids]++;
	data->ret[index][data->pp + 1] = i;
	while (i < data->pp)
	{
		i++;
		ids = get_smallest_path(data, index);
		if (manage_lap_ovf(data, i, ids) > lap)
		{
		//	lap = manage_lap_ovf(data, i, ids);
		//	data->ret[index][ids]++;
			break ;
		}
		lap = manage_lap_ovf(data, i, ids);
		data->ret[index][ids]++;
		data->ret[index][data->pp + 1] = i;
	}
	reset_marker_values(data);
	set_opti_tab_2(data, index, lap);
	return (lap);
}

t_bool	opti_path_len(t_data *data)
{
	UINT i;

	i = 0;
	while (i < data->pp)
	{
		if (data->ret[i][data->pp + 1] == 0)
		{
			FPF("break tamer\n");
			break ;
		}
		data->ret[i][data->pp] = set_opti_tab(data, i);
		i++;
	}
	return (true);
}
