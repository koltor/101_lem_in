/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_sorter_utils3.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/26 17:31:54 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 17:37:33 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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
