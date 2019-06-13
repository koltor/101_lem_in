/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recursive_bs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/30 14:38:15 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/13 16:07:50 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	set_children(t_turn *turn, UINT lap, UINT id_room, UINT id_path)
{
	turn->id_path = id_path;
	turn->id_room = id_room;
	turn->turn = lap;
	return (1);
}

UINT	lap_r_managment(t_data *dt, t_turn *turns, UINT id_turn, UINT old_child)
{
	UINT	i;
	UINT	children;
	t_turn	old_t;
	t_room	room;

	i = -1;
	children = 0;
	old_t = turns[id_turn];
	room = dt->r_tab[turns[id_turn].id_room];
	while (++i < room.nb_link_tubes)
		if (dt->t_tab[room.link_tubes[i]].path_id == ROOM_START)
		{
			dt->t_tab[room.link_tubes[i]].turn = turns[id_turn].turn + 1;
			dt->t_tab[room.link_tubes[i]].path_id = old_t.id_path;
			children += set_children(&turns[old_child + children],
			turns[id_turn].turn + 1, get_id_room(dt->t_tab[room.link_tubes[i]],
				old_t.id_room), old_t.id_path);
			if (get_id_room(dt->t_tab[room.link_tubes[i]], old_t.id_room) == ROOM_END)
				return (destroy_turn(turns, old_child, id_turn, children));
		}
	return (children);
}

UINT	lap_managment(t_data *data, t_turn *turns, UINT parent, UINT lap)
{
	UINT turn_id;
	UINT child;

	turn_id = 0;
	child = 0;
	while (turn_id < parent)
	{
		if (turns[turn_id].turn == lap - 1)
		{
			child += lap_r_managment(data, turns, turn_id, parent + child);
		}
		turn_id++;
	}
	return (child);
}

void	recursive_bs_turn(t_data *data, t_turn *turns, UINT parent, UINT lap)
{
	UINT children;

	children = lap_managment(data, turns, parent, lap);
	if (children)
		recursive_bs_turn(data, &turns[parent], children, ++lap);
}
