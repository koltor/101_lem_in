/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_sorter2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/24 16:46:51 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 21:37:43 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	max_paths(t_data data)
{
	if (data.r_tab[0].nb_link_tubes < data.r_tab[1].nb_link_tubes)
		return (data.r_tab[0].nb_link_tubes);
	return (data.r_tab[1].nb_link_tubes);
}

void	reset_markers(t_data *data)
{
	UINT i;

	i = 2; // attention segv si y aque start et end
	while (i < data->rooms)
	{
		if (data->r_tab[i].used == true)
			data->r_tab[i].used = false;
		i++;
	}
}

void	set_used_rooms(UINT id_tab, t_data *data)
{
	UINT i;

	i = 4;
	FPF("id tab = %u\n", id_tab);
	if (id_tab == data->path_nbr)
	{
		FPF("allo\n");
		return ;
	}
	while (i < data->paths[id_tab][1] - 1)
	{
		data->r_tab[data->paths[id_tab][i]].used = true;
		i++;
	}
}

UINT	is_valid(UINT *tab, t_data *data)
{
	UINT i;

	i = 4;
	while (i < tab[1] - 1)
	{
		if (data->r_tab[tab[i]].used == true)
			return (0);
		i++;
	}
	return (1);
}

UINT	get_compatible_tab_for_pid(UINT pid, t_data *data)
{
	UINT i;
	t_bool test;
	UINT ret;

	i = 0;
	test = false;
	ret = 0;
	while (data->paths[i] != NULL)
	{
		if (data->paths[i][0] == pid && data->paths[i][2] == NUSED && test == false && is_valid(data->paths[i], data))
		{
			ret = i;
			test = true;
		}
		if (test == true && data->paths[i][0] == pid && data->paths[i][2] == NUSED && data->paths[i][1] < data->paths[ret][1] && is_valid(data->paths[i], data))
			ret = i;
		i++;
	}
	if (test == false)
		ret = data->path_nbr;
	return (ret);
}
