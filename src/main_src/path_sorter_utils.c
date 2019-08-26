/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_sorter_utils.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 14:23:08 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 17:06:26 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	set_tab_zero(UINT (*tabc)[], UINT max_paths) // allo le pb is invalid for some reason dans cette fct
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		(*tabc)[i] = 0;
		i++;
	}
}

UINT 	count_id_paths(t_data data)
{
	UINT i;
	UINT ret;
	UINT cpid;
	UINT tab[4097];

	i = 0;
	ret = 0;
	cpid = 0;
	set_tab_zero(&tab, 4097);
	while (data.paths[i])
	{
		if (data.paths[i][0] != 0 && tab[data.paths[i][0]] == 0)
		{
			tab[data.paths[i][0]]++;
			ret++;
		}
		i++;
	}
	return (ret);
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

UINT	max_paths(t_data data)
{
	UINT max_paths;

	if (data.r_tab[0].nb_link_tubes < data.r_tab[1].nb_link_tubes)
		max_paths = data.r_tab[0].nb_link_tubes;
	max_paths = data.r_tab[1].nb_link_tubes;
	if (count_id_paths(data) < max_paths)
		max_paths = count_id_paths(data);
	return (max_paths);
}

void	reset_markers(t_data *data)
{
	UINT i;

	i = 2;
	if (data->rooms == 2)
		return ;
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
	if (data->paths[id_tab][i] == 1)
		return ;
	while (i < data->paths[id_tab][1] - 1)
	{
		data->r_tab[data->paths[id_tab][i]].used = true;
		i++;
	}
}

UINT	get_pnum(UINT pid, t_data *data)
{
	UINT i;
	UINT ret;

	i = 0;
	ret = 0;
	while (data->paths[i])
	{
		if (data->paths[i][0] == pid)
			ret++;
		i++;
	}
	return (ret);
}

UINT	get_min_pid(t_data *data, UINT max_paths)
{
	UINT i;
	UINT ret;

	i = 1;
	ret = data->paths[0][0];
	if (max_paths == 1)
		return (ret);
	while (i < max_paths)
	{
		if (data->paths[i][0] < ret)
			ret = data->paths[i][0];
		i++;
	}
	return (ret);
}

UINT	get_max_pid(t_data *data, UINT max_paths)
{
	UINT i;
	UINT ret;

	i = 1;
	ret = data->paths[0][0];
	if (max_paths == 1)
		return (ret);
	while (i < max_paths)
	{
		if (data->paths[i][0] > ret)
			ret = data->paths[i][0];
		i++;
	}
	return (ret);
}

UINT	get_size_valid_tab(t_data *data, UINT (*res)[], UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		if ((*res)[i] != data->path_nbr && data->paths[(*res)[i]][0] != 0)
		{
			data->paths[(*res)[i]][0] = 0;
			return (data->paths[(*res)[i]][1] - 4);
		}
		i++;
	}
	return (0);
}
UINT	get_index_valid_tab(t_data *data, UINT (*res)[], UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		if ((*res)[i] != data->path_nbr && data->paths[(*res)[i]][0] != 0)
			return (i);
		i++;
	}
	return (0);
}
