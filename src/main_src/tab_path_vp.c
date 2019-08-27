/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/17 11:24:26 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 11:31:06 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	del_2d_int_tab(UINT **tab)
{
	UINT i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	malloc_path_tabs_norm(t_data *data, UINT *j, UINT i, UINT pname)
{
	if (!(data->paths[*j] = (UINT *)malloc(sizeof(UINT) *
		(data->t_tab[data->r_tab[1].link_tubes[i]].tmp_turn[pname -
			1] + 4))))
	{
		f_error(ERR_MALLOC, NULL);
		return ;
	}
	data->paths[*j][0] = pname;
	data->paths[*j][1] =
	data->t_tab[data->r_tab[1].link_tubes[i]].tmp_turn[pname -
		1] + 4;
	data->paths[*j][2] = NUSED;
	*j += 1;
}

void	malloc_path_tabs(t_data *data)
{
	UINT	i;
	UINT	j;
	UINT	qt;
	UINT	pname;
	ULL		path_id_cp;

	i = 0;
	j = 0;
	qt = 0;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		path_id_cp = data->t_tab[data->r_tab[1].link_tubes[i]].path_id;
		qt = qt + count_bits(data->t_tab[data->r_tab[1].link_tubes[i]]);
		while (j < qt)
		{
			pname = find_pname(&path_id_cp, data->r_tab[0].nb_link_tubes);
			malloc_path_tabs_norm(data, &j, i, pname);
		}
		i++;
	}
}

UINT	fill_path_tab(t_data *data)
{
	UINT path_nb;

	if (!(path_nb = potential_path_counter(data)))
	{
		f_error(ERR_NO_PATHS, NULL);
		return (0);
	}
	data->path_nbr = path_nb;
	if (!(data->paths = (UINT **)malloc(sizeof(UINT *) * (path_nb + 1))))
	{
		f_error(ERR_MALLOC, NULL);
		return (0);
	}
	data->paths[path_nb] = NULL;
	malloc_path_tabs(data);
	return (1);
}
