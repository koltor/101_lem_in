/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   browse_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/30 12:35:26 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 16:19:26 by ocrossi     ###    #+. /#+    ###.fr     */
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

static t_turn	*init_turn(UINT size)
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
	t_tube *tube;

	i = 0;
	while (i < start.nb_link_tubes)
	{
		tube = &tubes[start.link_tubes[i]];
		tube->path_id = bin(i % start.nb_link_tubes + 1);
		tube->tmp_turn[i] = 1;
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

	if (!(turns = init_turn(data->tubes * data->r_tab[id_room].nb_link_tubes)))
		return (NULL);
	start_columns(data->r_tab[id_room], data->t_tab, turns, id_room);
	return (turns);
}



static t_bool	error_malloc_prepare(t_tube *tab, UINT size)
{
	UINT i;

	i = 0;
	while (i < size)
	{
		free(tab[i].tmp_turn);
		i += 1;
	}
	return (false);
}

static UINT		prepare_tubes(t_tube *tab, UINT size, UINT length)
{
	UINT i;
	UINT j;

	i = 0;
	while (i < size)
	{
		if (!(tab[i].tmp_turn = malloc(sizeof(UINT) * length)))
			return (i);
		j = 0;
		while (j < length)
		{
			tab[i].tmp_turn[j] = 0;
			j++;
		}
		i += 1;
	}
	return (0);
}

t_bool			browse_map(t_data *data)
{
	t_turn	*turns;
	UINT	ret;
	t_list	*paths;

	if ((ret = prepare_tubes(data->t_tab, data->tubes, data->r_tab[ROOM_START].nb_link_tubes)))
		return (error_malloc_prepare(data->t_tab, ret));
	if (!(turns = prepare_turn_to_start(data, ROOM_START)))
		return (false);
	recursive_bs_turn(data, turns, data->r_tab[ROOM_START].nb_link_tubes, 2);
	fill_path_tab(data);
	fill_tabs_with_rooms(data);
	path_sorter2(data, max_paths(*data));
	free(turns);
	return (true);
}
