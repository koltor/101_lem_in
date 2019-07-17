/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opti_len_paths1.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/17 16:34:33 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/17 21:05:50 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"


UINT	get_smallest_path_for_opti2(t_data *data, UINT (*tab)[], UINT index)
{
	UINT size;
	UINT ret;
	UINT i;

	i = 0;
	while ((*tab)[i] != 1)
		i++;
	size = data->ret[i][data->pp];
	ret = index;
	while (i < data->pp)
	{
	//	FPF("i = %u marker path %u index tab %u size %u\n", i, data->paths[i][2], index, size);
		if ((*tab)[i] == 1 && size >= data->paths[i][1] - 4 && data->paths[i][2] != USED)
		{
			size = data->paths[i][1] - 4;
			ret = i;
		}
		i++;
	}
	data->paths[ret][2] = USED;
	return (ret);
}


void	check_shorter_paths_than_lap(t_data *data, UINT lap, UINT (*tab)[], UINT index)
{
	UINT i;

	i = 0;
	while (i < data->pp)
	{
		if (data->paths[i][1] - 4 < lap && data->ret[index][i] == 1)
		{
			(*tab)[i] = 1;
			(*tab)[data->pp]++;
		}
		i++;
	}
	print_tab(tab, data->pp);
}

void	set_opti_with_new_paths(t_data *data, UINT lap, UINT (*tab)[], UINT index) // mm chose avec le nv tab mais dns l aurte snes, cf feuilles woulah
{
	UINT lap_cp;
	UINT ant_cp;
	UINT ids;
	UINT i;

	i = 0;
	ant_cp = data->ants;
	ids = get_smallest_path_for_opti2(data, tab, index);
	lap_cp = lap;
	while (i < (*tab)[data->pp])
	{
		if (i != 0 && lap >= lap_cp)
			break ;
		data->ants--;
//		lap = (manage_lap_ovf(data, i, ids) > data->paths[i][1] - 4 + i) ? ma; la il faut prendre le plus grand entre le nv lap et la len du chemin + nb de passage
		i++;	
	}
}

UINT	set_opti_tab_2(t_data *data, UINT index, UINT lap)
{
	UINT tab[data->pp + 1];

	set_tab_zero(&tab, (data->pp + 1));
	check_shorter_paths_than_lap(data, lap, &tab, index);
	set_opti_with_new_paths(data, lap, &tab, index);
//	get_paths_nbr(data, &tab, index); letzter Schritt
	return (0);
}
