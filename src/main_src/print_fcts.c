/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_fcts.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/12 16:29:55 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/12 16:49:52 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	print_tab(UINT (*res)[], UINT max_paths)
{
	UINT tst = 0;

	FPF("====================================================================\n");
	while (tst < max_paths)
	{
		FPF("case num %u tab num %u\n", tst, (*res)[tst]);
		tst++;
	}
	FPF("====================================================================\n");
}

void	print_potential_paths(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	j = 0;
	FPF("nb de chemins trouves = %u\n", potential_path_counter(data));
	while (data->paths[i] != NULL)
	{
		j = 3;
		FPF("tab num %u id_path = %u size = %u\n", i, data->paths[i][0], data->paths[i][1]);
		while (j < data->paths[i][1])
		{
			FPF("salle %u name = %s\n", j, data->r_tab[data->paths[i][j]].name);
			j++;
		}
		FPF("-----------------------------------\n");
		i++;
	}
}

void	print_one_potential_path(t_data *data, UINT i)
{
	UINT j;

	j = 3;
	FPF("tab num %u id_path = %u size = %u\n", i, data->paths[i][0], data->paths[i][1]);
	while (j < data->paths[i][1])
	{
		FPF("salle %u name = %s\n", j, data->r_tab[data->paths[i][j]].name);
		j++;
	}
}


void	print_final_path_tab(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (data->ret[i])
	{
		j = 1;
		while (j < data->ret[i][0])
		{
			FPF("alle %s\n", data->r_tab[data->ret[i][j]].name);
			j++;
		}
		i++;
	}
	data->path_nbr = i;
}

void	print_cp_tab_binary(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (data->ret[i])
	{
		if (data->ret[i][data->pp + 1] == 0)
		{
			FPF("heyyyyy le break ?\n");
	//		break ;
		}
		j = 0;
		FPF("\nret index %u nb de chemins trouves = %u taille du plus grand chemin trouve = %u\n", i, data->ret[i][data->pp + 1], data->ret[i][data->pp]);
		while (j < data->pp)
		{
			FPF(" %u ", data->ret[i][j]);
			j++;
		}
		i++;
		FPF("\n---------------------------\n");
	}
}

void	print_comp_tab(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (data->ret[i])
	{
		j = 0;
		FPF("ret index %u nb de chemins trouves = %u taille du plus grand chemin trouve = %u\n", i, data->ret[i][data->pp + 1], data->ret[i][data->pp]);
		while (j < data->pp)
		{
			if (data->ret[i][j] == 1)
			{
				FPF("\nle tab %u est compatible\n", j);
				print_one_potential_path(data, j);
			}
			j++;
		}
		FPF("\n---------------------------\n");
		i++;
	}
}