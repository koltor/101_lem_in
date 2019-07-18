/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   opti_len_paths1.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/17 16:34:33 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/18 18:20:54 by ocrossi     ###    #+. /#+    ###.fr     */
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
	while ((*tab)[i] != 1 && i < data->pp)
		i++;
	if (i == data->pp)
		return (data->pp + 2);
	size = data->ret[i][data->pp];
	ret = index;
//	i = 0;
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


void	sort_shorter_paths_than_lap(t_data *data, UINT lap, UINT (*tab)[], UINT index)
{
	UINT i;
	UINT j;
	UINT ids;

	i = 0;
	j = 1;
	while (i < data->pp)
	{
		ids = get_smallest_path_for_opti2(data, tab, index);		
		if ((ids == data->pp + 2) || data->paths[ids][1] - 4 >= lap)
		{
	//		FPF("ids %u res %u lap %u\n", ids, data->paths[ids][1] - 4, lap);
			break ;
		}
		(*tab)[ids] = j;
		j++;
		(*tab)[data->pp]++;
		i++;
	}
//	print_tab_with_size(data, tab, data->pp);
}

void	check_shorter_paths_than_lap(t_data *data, UINT lap, UINT (*tab)[], UINT index)
{
	UINT i;
	//UINT ids;

	i = 0;
	while (i < data->pp)
	{
		if (data->paths[i][1] - 4 < lap && data->paths[i][2] != USED)
		{
			(*tab)[i] = 1;
			(*tab)[data->pp]++;

		//	FPF("ids %u res %u lap %u\n", ids, data->paths[ids][1] - 4, lap);
		//	break ;
		}
		i++;
	}
//	print_tab_with_size(data, tab, data->pp);
}


void	set_opti_with_new_paths(t_data *data, UINT lap, UINT (*tab)[], UINT index) // mm chose avec le nv tab mais dns l aurte snes, cf feuilles woulah
{
	UINT lap_cp;
	UINT ant_cp;
	UINT ids;
	UINT i;
	
	UINT mres;
	UINT what;

	i = 0;
	ant_cp = data->ants;
	ids = get_smallest_path_for_opti2(data, tab, index);
	//FPF("arrive dans set opti lap = %u ids = %u\n", lap, ids);
	lap_cp = lap;
	while (i < (*tab)[data->pp])
	{
		if (i != 0 && (lap >= lap_cp || i == 2 || data->ants == 1))// derniere condi pas forcement necessaire
			break ;
		data->ants--;
		i++;
		//FPF("hey ids %u\n", ids);
		mres = manage_lap_ovf(data, i, ids);
		FPF("ho\n");
		what = data->paths[ids][1] - 4 + (i - 1);
		FPF("set opti with new tab la taille du chemin normal av 1 fourmi en moins %u par rapport a l ancien %u\n", mres, lap_cp);
		FPF("la taille du chemin normal qu on va greffer %u i = %u\n", what, i);
//		lap = (manage_lap_ovf(data, i, ids) > data->paths[i][1] - 4 + i) ? ma; la il faut prendre le plus grand entre le nv lap et la len du chemin + nb de passage
	}
	data->ants = ant_cp;
}

UINT	set_opti_tab_2(t_data *data, UINT index, UINT lap, UINT (*tcpt)[])
{
	UINT tab[data->pp + 1];

	set_tab_zero(&tab, (data->pp + 1));

	check_shorter_paths_than_lap(data, lap, &tab, index);
	sort_shorter_paths_than_lap(data, lap, &tab, index);
	FPF("BONJOUR SHORTER PATH lap = %u tab =\n", lap);
	print_tab_with_size(data, &tab, data->pp);
	FPF("BONJOUR tab d entree  =\n");
	print_tab_with_size(data, tcpt, data->pp);

//	reset_marker_values(data);
//	set_opti_with_new_paths(data, lap, &tab, index);
	return (0);
}
