/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:22:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 15:36:14 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	show_room(t_room *r_tab, UINT size)
{
	UINT i;

	i = 0;
	dprintf(1, "\n------Les Salles Apres Stockage---------------\n");
	dprintf(1, "ID    Status        Nom     X     Y      \n");
	while (i < size)
	{
		if (i == 0)
			dprintf(1, "%-5u %6s %10s %5d %5d --> Debut\n", i, "Debut:",
							r_tab[i].name, r_tab[i].x, r_tab[i].y);
		else if (i == 1)
			dprintf(1, "%-5u %6s %10s %5d %5d --> Fin\n", i, "Fin:",
							r_tab[i].name, r_tab[i].x, r_tab[i].y);
		else
			dprintf(1, "%-5u salle: %10s %5d %5d\n", i,
							r_tab[i].name, r_tab[i].x, r_tab[i].y);
		i++;
	}
	dprintf(1, "-------------------Fin------------------------\n");
}

static void	show_tube(t_tube *t_tab, UINT size, t_room *r_tab)
{
	UINT i;

	i = 0;
	dprintf(1, "\n------Les Chemins Apres Stockage---------------\n");
	dprintf(1, "id-s1      id-s2      Salle1        Salle2\n");
	while (i < size)
	{
		dprintf(1, " %-4u --- %4u    ", t_tab[i].salle1, t_tab[i].salle2);
		dprintf(1, "  %-10s --- %10s\n", r_tab[t_tab[i].salle1].name,
											r_tab[t_tab[i].salle2].name);
		i++;
	}
	dprintf(1, "-------------------Fin-------------------------\n\n");
}

void		debug_lem_in(t_data *data)
{
	dprintf(1, "-----------Information General----------------\n");
	dprintf(1, "salle:%4u    tube:%4u    fourmis:%5u\n", data->rooms,
												data->tubes, data->ants);
	show_room(data->r_tab, data->rooms);
	show_tube(data->t_tab, data->tubes, data->r_tab);
}

void		debug_main(int option)
{
	char d;

	d = *(char*)f_error(0, NULL);
	dprintf(1, "     option: %d                Error: %d\n", option, (int)d);
	str_error((int)d);
}
