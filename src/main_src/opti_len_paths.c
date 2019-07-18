/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opti_len_paths.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/18 19:47:15 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/18 19:59:54 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opti_len_paths.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/16 13:05:25 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/18 19:30:44 by ocrossi     ###    #+. /#+    ###.fr     */
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

	FPF("ants %u i %u ids %u\n", data->ants, i, ids);
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
	FPF("end of mlo lap = %u\n", lap);
	return (lap);
}
void	insert_ant_counter(t_data *data, UINT index, UINT (*tab)[])
{
	UINT i;
//	UINT j;
	UINT res;
	UINT res_ovf;
	UINT ovf;

	res = data->ants / data->ret[index][data->pp + 1];
	res_ovf = data->ants % data->ret[index][data->pp + 1];
	i = 0;
	while (i < data->pp)
	{
		
		i++;
	}
	FPF("bonjour dans insert ant counter le nb de chemins trouves %u\n", data->ret[index][data->pp + 1]);
}

UINT	set_opti_tab(t_data *data, UINT index, UINT (*tab)[])// pb de lap counter
{
	UINT i;
	UINT ids;
	UINT lap;

	i = 1;
	ids = get_smallest_path(data, index);
	lap = manage_lap_ovf(data, i, ids);
	(*tab)[ids] = i;
	data->ret[index][ids]++;
	data->ret[index][data->pp + 1] = i;
	while (i < data->pp)
	{
		i++;
		ids = get_smallest_path(data, index);
		if (manage_lap_ovf(data, i, ids) > lap)
			break ;
		lap = manage_lap_ovf(data, i, ids);
		data->ret[index][ids]++;
		data->ret[index][data->pp + 1] = i;
		(*tab)[ids] = i;
	}
//	print_tab_with_size(data, tab, data->pp);
//	insert_ant_counter(data, index, tab); not yet
	return (lap);
}

void	set_tab_for_ants(t_data *data, UINT ids1, UINT ids2, UINT (*tab)[])
{
	if (data->paths[ids1][1] == data->paths[ids1][2])
	{
		while (
		return ;
	}
	
	while (i < data->pp)
	{
		 (*tab)[get_smallest_path(data, index)] = i + 1;
		i++;
	}
	print_tab_with_size(data, tab, data->pp);
}

void	get_2_smallest(t_data *data,  UINT (*tab)[])
{
	(*tab)[data->pp + 1] = get_smallest_path(data, (*tab)[data->pp]);
	(*tab)[data->pp + 2] = get_smallest_path(data, (*tab)[data->pp]);
	data->paths[(*tab)[data->pp + 2]][2] = NUSED;
}

//void	set_cell(t_data *data, 

UINT	new_algo_sa_mere(t_data *data, UINT(*tab)[])
{
	UINT lap;
	UINT i;
	UINT ants;

	i = 0;
	ants = data->ants;
	reset_marker_values(data);
/*	if (cas_particulier 1 chemin)
		ftc 1 chemin
		return*/
	lap = 0;
	while (ants)
	{
		get_ids_smallest(data, tab);
		while (data->paths[tab[data->pp + 1] < 
	//	set_tab_for_ants(data, ids1, ids2, tab);
	//	set_cell(data, &ids1, &ids2, index);
		i++;
	}
	// copier tab dans ret
	return (lap);
}

t_bool	opti_path_len(t_data *data)
{
	UINT i;
	UINT tcpt[data->pp + 5];

	i = 0;
	set_tab_zero(&tcpt, data->pp);
	while (i < data->pp)
	{
		if (data->ret[i][data->pp + 1] == 0)
		{
			FPF("break tamer\n");
			break ;
		}
		tcpt[data->pp] = i;
		data->ret[i][data->pp] = new_algo_sa_mere(data, &tcpt);
//		data->ret[i][data->pp] = set_opti_tab(data, i, &tcpt);
//		set_opti_tab_2(data, i, data->ret[i][data->pp], &tcpt);
//		reset_marker_values(data);
		i++;
	}
	return (true);
}
