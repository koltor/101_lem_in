/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   browse_map2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/26 18:20:32 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 18:23:45 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** INFORMATION YOU NEED TO KNOW BEFORE READ THIS FILE
**	- a columns is a path we send at the start of the algo
*/

/*
** init_turn:
**	the function prepare the turn_board with malloc
**	and set every cell of the turn_board in 0
**	parameters
**		need the number of tubes
**	return value
**		the board if all is right
**		NULL otherwise
*/

t_turn			*init_turn(UINT size)
{
	UINT	i;
	t_turn	*turns;

	i = 0;
	if (!(turns = malloc(sizeof(t_turn) * size)))
		return (f_error(ERR_MALLOC, NULL));
	while (i < size)
	{
		turns[i].id_room = 0;
		turns[i].id_path = 0;
		turns[i].turn = 0;
		i++;
	}
	return (turns);
}

/*
** get_id_room:
**	the function return the id of the room your not in a tube
**	parameters
**		the tube you want to ask
**		the id of the room were you are
**	return value
**		the id of the room your not
*/

UINT			get_id_room(t_tube tubes, UINT id_room)
{
	if (tubes.salle1 == id_room)
		return (tubes.salle2);
	return (tubes.salle1);
}
