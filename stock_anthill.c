/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stock_anthill.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 10:57:56 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 16:01:08 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*new_room(int x, int y, char *name, char salle_id)
{
	t_room	*room;

	if (!(room = malloc(sizeof(t_room))))
		return (NULL);
	if (name == NULL)
		room->name = NULL;
	else if (!(room->name = ft_strdup(name)))
	{
		free(room);
		return (NULL);
	}
	room->salle_id = (UINT)salle_id;
	room->x = x;
	room->y = y;
	room->next = NULL;
	return (room);
}

void	free_room(t_room *room)
{
	t_room *tmp;

	while (room)
	{
		if (room->name)
			free(room->name);
		tmp = room;
		room = room->next;
		free(tmp);
	}
}

t_tube	*new_tube(UINT id_salle1, UINT id_salle2)
{
	t_tube *tube;

	if (!(tube = malloc(sizeof(t_tube))))
		return (NULL);
	tube->next = NULL;
	tube->salle1 = id_salle1;
	tube->salle2 = id_salle2;
	return (tube);
}

void	free_tube(t_tube *tube)
{
	t_tube *tmp;

	while (tube)
	{
		tmp = tube;
		tube = tube->next;
		free(tmp);
	}
}
