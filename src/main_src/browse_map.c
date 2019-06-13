/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   browse_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/30 12:35:26 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/13 16:40:26 by ocrossi     ###    #+. /#+    ###.fr     */
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

static t_turn	*init_turn(UINT tubes)
{
	UINT	i;
	t_turn	*turns;

	i = 0;
	if (!(turns = malloc(sizeof(t_turn) * tubes)))
		return (f_error(ERR_MALLOC, NULL));
	while (i < tubes)
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

/*
** start_columns:
**	fill the first cell of the turn_board with the different tubes of the
**	columns
**	parameters
**		the number of the columns
**		the room start
**		the tubes_board
**		the turn_board
*/

static void		start_columns(t_room start, t_tube *tubes, t_turn *turns, UINT id_room)
{
	UINT i;

	i = 0;
	while (i < start.nb_link_tubes)
	{
		tubes[start.link_tubes[i]].path_id = i % start.nb_link_tubes + 1;
		tubes[start.link_tubes[i]].turn = 1;
		turns[i].id_path = i % start.nb_link_tubes + 1;
		turns[i].id_room = get_id_room(tubes[start.link_tubes[i]], id_room);
		turns[i].turn = 1;
		i++;
	}
}

t_turn	*prepare_turn_to_start(t_data *data, UINT id_room)
{
	t_turn	*turns;
	UINT	nbr_col;

	if (!(turns = init_turn(data->tubes)))
		return (NULL);
	start_columns(data->r_tab[id_room], data->t_tab, turns, id_room);
	return (turns);
}

t_bool			browse_map(t_data *data)
{
	t_turn	*turns;
	t_list	*paths;

	if (!(turns = prepare_turn_to_start(data, ROOM_START)))
		return (false);
	recursive_bs_turn(data, turns, data->r_tab[ROOM_START].nb_link_tubes, 2);
	paths = get_id_path_list(data->r_tab[1], data);
	stock_rooms_to_go(paths, data);
	free(turns);
	return (true);
}
