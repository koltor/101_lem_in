/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recursive_bs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/30 14:38:15 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/04 20:51:28 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	destroy_path(t_turn *turns, UINT parent, UINT id_turn, UINT child)
{
	while (++id_turn < parent + child)
	{
		if (turns[id_turn].id_path == turns[id_turn].id_path)
		{
			turns[id_turn].turn = turns[id_turn].turn - 1;
		}
	}
	return (child);
}

void	set_parent(t_tube *tube, UINT lap, UINT id_path)
{
	tube->path_id = id_path;
	tube->turn = lap;
}

UINT	set_children(t_turn *turn, UINT lap, UINT id_room, UINT id_path)
{
	turn->id_path = id_path;
	turn->id_room = id_room;
	turn->turn = lap;
	return (1);
}

UINT	lap_room_managment(t_tube *tubes, t_room *room, t_turn *turns, UINT lap, UINT id_turn, UINT old_children)
{
	UINT i;
	UINT children;
	UINT room_id;

	i = 0;
	children = 0;
	while (i < room->nb_link_tubes)
	{
		if (tubes[room->link_tubes[i]].path_id == 0)
		{
			room_id = get_id_room(tubes[room->link_tubes[i]], turns[id_turn].id_room);
			set_parent(&tubes[room->link_tubes[i]], lap, turns[id_turn].id_path);
			children += set_children(&turns[old_children + children], lap, room_id, turns[id_turn].id_path);
			if (get_id_room(tubes[room->link_tubes[i]], turns[id_turn].id_room) == 1)
				return (destroy_path(turns, old_children, id_turn, children));
		}
		i++;
	}
	return (children);
}

UINT	lap_managment(t_data *data, t_turn *turns, UINT parent, UINT lap)
{
	UINT id_turn;
	UINT children;

	id_turn = 0;
	children = 0;
	while (id_turn < parent)
	{
		if (turns[id_turn].turn == lap - 1)
		{
			children += lap_room_managment(data->t_tab,
				&data->r_tab[turns[id_turn].id_room], turns, lap, id_turn, parent + children);
		}
		id_turn++;
	}
	return (children);
}

void	recursive_bs_turn(t_data *data, t_turn *turns, UINT parent, UINT lap)
{
	UINT children;

	children = lap_managment(data, turns, parent, lap);
	if (children)
		recursive_bs_turn(data, &turns[parent], children, ++lap);
}
