/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:22:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/18 15:15:47 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void		show_room(t_room *r_tab, UINT size)
{
	UINT i;

	i = 0;
	dprintf(1, "\n------------Les Salles Apres Stockage-----------------\n");
	dprintf(1, "ID    Status        Nom     X     Y             liens\n");
	while (i < size)
	{
		if (i == 0)
			dprintf(1, "%-5u %6s %10s %5d %5d --> Debut   %5d\n", i, "Debut:",
				r_tab[i].name, r_tab[i].x, r_tab[i].y, r_tab[i].nb_link_tubes);
		else if (i == 1)
			dprintf(1, "%-5u %6s %10s %5d %5d --> Fin     %5d\n", i, "Fin:",
				r_tab[i].name, r_tab[i].x, r_tab[i].y, r_tab[i].nb_link_tubes);
		else
			dprintf(1, "%-5u salle: %10s %5d %5d             %5d\n", i,
				r_tab[i].name, r_tab[i].x, r_tab[i].y, r_tab[i].nb_link_tubes);
		i++;
	}
	dprintf(1, "----------------------------Fin-----------------------\n");
}

static void		show_tube(t_tube *t_tab, UINT size, t_room *r_tab)
{
	UINT i;

	i = 0;
	dprintf(1, "\n------Les Chemins Apres Stockage------------------------\n");
	dprintf(1, " id-s1   id-s2      Salle1           Salle2  chemin   tour\n");
	while (i < size)
	{
		dprintf(1, " %-4u --- %4u    ", t_tab[i].salle1, t_tab[i].salle2);
		dprintf(1, "  %-9s --- %9s    %4llu %4u\n", r_tab[t_tab[i].salle1].name,
				r_tab[t_tab[i].salle2].name, t_tab[i].path_id, t_tab[i].turn);
		i++;
	}
	dprintf(1, "-------------------Fin----------------------------------\n\n");
}

static void		show_tab_tubes(UINT id_r, t_data *data)
{
	UINT i;
	UINT j;
	UINT size;

	i = 0;
	size = data->r_tab[id_r].nb_link_tubes;
	dprintf(1, "------------------Information noeuds ------------------\n");
	dprintf(1, "nom de la salle actuelle: %s\n\n", data->r_tab[id_r].name);
	dprintf(1, "id du tube        nom des salles      id_path  turn\n");
	while (size)
	{
		dprintf(1, " %-10u%15s-%-15s%llu%5u\n", data->r_tab[id_r].link_tubes[i],
		data->r_tab[data->t_tab[data->r_tab[id_r].link_tubes[i]].salle1].name,
		data->r_tab[data->t_tab[data->r_tab[id_r].link_tubes[i]].salle2].name,
		data->t_tab[data->r_tab[id_r].link_tubes[i]].path_id,
		data->t_tab[data->r_tab[id_r].link_tubes[i]].turn);
		j = 0;
		dprintf(1, "[");
		while (j < data->r_tab[ROOM_START].nb_link_tubes)
		{
			dprintf(1, "%5d ", data->t_tab[data->r_tab[id_r].link_tubes[i]].tmp_turn[j]);
			j++;
		}
		i++;
		size--;
		dprintf(1, "]\n");
	}
	dprintf(1, "-------------------Fin---------------------------------\n\n");
}

static void		g_show_tab_tubes(t_data *data)
{
	UINT	i;

	i = 0;
	if (data->rooms == 0)
		return ;
	while (i < data->rooms)
	{
		show_tab_tubes(i, data);
		i++;
	}
}

void			debug_lem_in(t_data *data)
{
	show_room(data->r_tab, data->rooms);
	show_tube(data->t_tab, data->tubes, data->r_tab);
	g_show_tab_tubes(data);
}
