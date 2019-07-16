/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opti_len_paths.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/16 13:05:25 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/16 16:58:27 by ocrossi     ###    #+. /#+    ###.fr     */
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

void	set_opti_tab(t_data *data, UINT index)// pb de lap counter
{
	UINT i;
	UINT ids;
	UINT lap;

	i = 1;
	ids = get_smallest_path(data, index);
	lap = (data->ants % i != 0 && data->paths[data->ants % i - 1][1] == data->paths[ids][1]) ? data->ants / i + data->paths[ids][1] - 3 : data->ants / i + data->paths[ids][1] - 4; // il faut raj l overflow
	//lap = data->ants / i + data->paths[ids][1] - 4; // il faut raj l overflow
	FPF("debut lap = %u\n", lap);
	while (i < data->pp)
	{
		i++;
		ids = get_smallest_path(data, index); //  penser a set le tab a used
		if (data->ants / i + data->paths[ids][1] - 4 > lap) // pb de calcul
		{
			FPF("we should break tameri i = %u\n", i);
			//lap = data->ants / i + data->paths[ids][1] - 4;
				lap = (data->ants % i != 0 && data->paths[data->ants % i - 1][1] == data->paths[ids][1]) ? data->ants / i + data->paths[ids][1] - 3 : data->ants / i + data->paths[ids][1] - 4; // il faut raj l overflow
			data->ret[index][ids]++;
			break ;
		}
		//lap = data->ants / i + data->paths[ids][1] - 4;
		lap = (data->ants % i != 0 && data->paths[data->ants % i - 1][1] == data->paths[ids][1]) ? data->ants / i + data->paths[ids][1] - 3 : data->ants / i + data->paths[ids][1] - 4; // il faut raj l overflow
		FPF("dans traitement lap = %u ids = %u\n", lap, ids);
		data->ret[index][ids]++;
	}
	FPF("fin traitement lap = %u ids = %u\n", lap, ids);
	// raj le +1 si on prend un tab precedent avec une valeur egale
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
		set_opti_tab(data, i);
		i++;
	}
	return (true);
}
