/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/17 11:24:26 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/18 20:40:55 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	path_counter(t_data *data)
{
	UINT tab_id[data->r_tab[1].nb_link_tubes];
	UINT i;
	UINT j;
	UINT ret;

	i = 0;
	ret = 0;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		tab_id[i] = data->t_tab[data->r_tab[1].link_tubes[i]].path_id;
		i++;
	}
	i = 0;
	if (tab_id[0] != 0)
		ret++;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		j = i + 1;
		while (j < data->r_tab[1].nb_link_tubes)
		{
			if (j != i && tab_id[j] != tab_id[i] && tab_id[j] != 0 && tab_id[i] != 0)
			{
				ret++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (ret);
}

UINT	find_smallest_path(t_data *data)
{
	UINT i;
	UINT ret;
	UINT smallest;

	i = 0;
	while (data->t_tab[data->r_tab[1].link_tubes[i]].path_id == 0 &&
			i < data->r_tab[1].nb_link_tubes)
		i++;
	if (i == data->r_tab[1].nb_link_tubes)
		exit(EXIT_FAILURE); // a refaire au propre
	if (data->t_tab[data->r_tab[1].link_tubes[i]].used == true)
	{
		while (i < data->r_tab[1].nb_link_tubes)
		{
			if (data->t_tab[data->r_tab[1].link_tubes[i]].used == false)
				break ;
			i++;
		}
	}
	ret = i;
	smallest = data->t_tab[data->r_tab[1].link_tubes[i]].turn;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		if (smallest >= data->t_tab[data->r_tab[1].link_tubes[i]].turn &&
				data->t_tab[data->r_tab[1].link_tubes[i]].used == false &&
				data->t_tab[data->r_tab[1].link_tubes[i]].path_id != 0)
		{
			smallest = data->t_tab[data->r_tab[1].link_tubes[i]].turn;
			ret = i;
		}
		i++;
	}
	return (ret);
}

/*
void	malloc_path_tabs(t_data *data)
{
	UINT i;
	UINT index;

	i = 0;
	while (i < data->path_nbr)
	{
		printf("ALLO TA MERE\n");
		index = find_smallest_path(data);
		printf("index = %u\n", index);
		data->t_tab[data->r_tab[1].link_tubes[index]].used = true;
		if (!(data->paths[i] = (UINT *)malloc(sizeof(UINT) * (data->t_tab[data->r_tab[1].link_tubes[index]].turn + 3))))
		{
			f_error(ERR_MALLOC, NULL);
			return ;
		}
		data->paths[i][0] = data->t_tab[data->r_tab[1].link_tubes[index]].path_id;
		printf("allo le path id %u\n", data->paths[i][0]);
		data->paths[i][1] = data->t_tab[data->r_tab[1].link_tubes[index]].turn + 3;
		i++;
	}
}*/

UINT	find_pname(UINT path_id)
{

}

void	malloc_path_tabs(t_data *data)
{
	UINT i;
	UINT j;
	UINT qt;
	UINT pname;

	i = 0;
	j = 0;
	qt = 0;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		//data->t_tab[data->r_tab[1].link_tubes[index]].used = true;
		qt = qt + count_bits(data->t_tab[data->r_tab[1].link_tubes[i]].path_id);
		printf("qt = %u pour un path id de %u\n", qt, data->t_tab[data->r_tab[1].link_tubes[i]].path_id);
		while (j < qt)
		{
			pname = find_pname(data->t_tab[data->r_tab[1].link_tubes[i]].path_id) - 1;
			if (!(data->paths[j] = (UINT *)malloc(sizeof(UINT) * (data->t_tab[data->r_tab[1].link_tubes[i]].tmp_turn[pname] + 3))))
			{
				f_error(ERR_MALLOC, NULL);
				return ;
			}
			data->paths[i][0] = data->t_tab[data->r_tab[1].link_tubes[index]].path_id;
			data->paths[i][1] = data->t_tab[data->r_tab[1].link_tubes[index]].turn + 3;
			j++;
		}
		i++;
	}
}

void	fill_path_tab(t_data *data)
{
	UINT path_nb;

	path_nb = potential_path_counter(data);
	data->path_nbr = path_nb;
	printf("path counter = %u\n", path_nb);
	if (!(data->paths = (UINT **)malloc(sizeof(UINT *) * (path_nb + 1))))
	{
		f_error(ERR_MALLOC, NULL);
		return ;
	}
	data->paths[path_nb] = NULL;
	malloc_path_tabs(data);
}
