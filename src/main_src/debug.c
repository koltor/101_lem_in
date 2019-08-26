/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:22:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 17:20:13 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void		show_room(t_room *r_tab, UINT size)
{
	UINT i;

	i = 0;
	FPF("\n------------Les Salles Apres Stockage-----------------\n");
	FPF("ID    Status        Nom     X     Y             liens\n");
	while (i < size)
	{
		if (i == 0)
			FPF("%-5u %6s %10s %5d %5d --> Debut   %5d\n", i, "Debut:",
				r_tab[i].name, r_tab[i].x, r_tab[i].y, r_tab[i].nb_link_tubes);
		else if (i == 1)
			FPF("%-5u %6s %10s %5d %5d --> Fin     %5d\n", i, "Fin:",
				r_tab[i].name, r_tab[i].x, r_tab[i].y, r_tab[i].nb_link_tubes);
		else
			FPF("%-5u salle: %10s %5d %5d             %5d\n", i,
				r_tab[i].name, r_tab[i].x, r_tab[i].y, r_tab[i].nb_link_tubes);
		i++;
	}
	FPF("----------------------------Fin-----------------------\n");
}

static void		show_tube(t_tube *t_tab, UINT size, t_room *r_tab)
{
	UINT i;

	i = 0;
	FPF("\n------Les Chemins Apres Stockage------------------------\n");
	FPF(" id-s1   id-s2      Salle1           Salle2  chemin   tour\n");
	while (i < size)
	{
		FPF(" %-4u --- %4u    ", t_tab[i].salle1, t_tab[i].salle2);
		FPF("  %-9s --- %9s    %4llu %4u\n", r_tab[t_tab[i].salle1].name,
				r_tab[t_tab[i].salle2].name, t_tab[i].path_id, t_tab[i].turn);
		i++;
	}
	FPF("-------------------Fin----------------------------------\n\n");
}

static void		show_tab_tubes(UINT z, t_data *data)
{
	UINT i;
	UINT j;
	UINT size;

	i = 0;
	size = data->r_tab[z].nb_link_tubes;
	while (size--)
	{
		FPF(" %-10u%15s-%-15s%llu%5u\n", data->r_tab[z].link_tubes[i],
		data->r_tab[data->t_tab[data->r_tab[z].link_tubes[i]].salle1].name,
		data->r_tab[data->t_tab[data->r_tab[z].link_tubes[i]].salle2].name,
		data->t_tab[data->r_tab[z].link_tubes[i]].path_id,
		data->t_tab[data->r_tab[z].link_tubes[i]].turn);
		j = 0;
		FPF("[");
		while (j < data->r_tab[ROOM_START].nb_link_tubes)
		{
			if (data->t_tab[data->r_tab[z].link_tubes[i]].tmp_turn == NULL)
				break ;
			FPF("%5d ", data->t_tab[data->r_tab[z].link_tubes[i]].tmp_turn[j]);
			j++;
		}
		i++;
		FPF("]\n");
	}
}

static void		g_show_tab_tubes(t_data *data)
{
	UINT	i;

	i = 0;
	if (data->rooms == 0)
		return ;
	while (i < data->rooms)
	{
		FPF("------------------Information noeuds ------------------\n");
		FPF("nom de la salle actuelle: %s\n\n", data->r_tab[i].name);
		FPF("id du tube        nom des salles      id_path  turn\n");
		show_tab_tubes(i, data);
		FPF("-------------------Fin---------------------------------\n\n");
		i++;
	}
}

void			debug_lem_in(t_data *data)
{
	show_room(data->r_tab, data->rooms);
	show_tube(data->t_tab, data->tubes, data->r_tab);
	g_show_tab_tubes(data);
}
