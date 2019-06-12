/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recursive_bs_destroy.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/05 17:40:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/12 17:21:04 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	destroy_path(t_tube *tubes, t_room room, UINT id)
{
	UINT turn;
	UINT id_path;

	turn = tubes[room.link_tubes[id]].turn;
	id_path = tubes[room.link_tubes[id]].path_id;
/*	while (++id < room.nb_link_tubes)
	{
		tubes[room.link_tubes[id]].turn = turn;
		tubes[room.link_tubes[id]].path_id = id_path;
	}*/
}

UINT	destroy_turn(t_turn *turns, UINT old_children, UINT id_turn, UINT child)
{
	UINT ipath;

	ipath = turns[id_turn].id_path;
	while (++id_turn < old_children + child)
	{
		if (turns[id_turn].id_path == ipath)
			turns[id_turn].turn = 0;
	}
	return (child);
}
