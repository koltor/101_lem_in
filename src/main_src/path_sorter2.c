/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_sorter2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/24 16:46:51 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 16:49:14 by ocrossi     ###    #+. /#+    ###.fr     */
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
