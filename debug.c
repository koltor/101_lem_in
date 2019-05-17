/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 15:07:21 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 15:51:03 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	show_room(t_room *room)
{
	while (room)
	{
		dprintf(1, "%s %d %d %u", room->name, room->x, room->y, room->salle_id);
		if (room->salle_id == 1)
			dprintf(1, " --> Debut");
		else if (room->salle_id == 2)
			dprintf(1, " --> Fin");
		dprintf(1, "\n");
		room = room->next;
	}
}

void	show_tube(t_tube *tube)
{
	while (tube)
	{
		dprintf(1, "salle_id: %u <--> %u\n", tube->salle1, tube->salle2);
		tube = tube->next;
	}
}
