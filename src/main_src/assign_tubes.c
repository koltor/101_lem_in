/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   assign_tubes.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/30 12:35:26 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/12 15:17:30 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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

static UINT		get_nbr_columns(t_room start, t_room end)
{
	return (start.nb_link_tubes);
}

UINT			get_id_room(t_tube tubes, UINT id_room)
{
	if (tubes.salle1 == id_room)
		return (tubes.salle2);
	return (tubes.salle1);
}

static void		start_columns(UINT nb_columns, t_room *start,
											t_tube *tubes, t_turn *turns)
{
	UINT i;

	i = 0;
	while (i < start->nb_link_tubes)
	{
		tubes[start->link_tubes[i]].path_id = i % nb_columns + 1;
		tubes[start->link_tubes[i]].turn = 1;
		turns[i].id_path = i % nb_columns + 1;
		turns[i].id_room = get_id_room(tubes[start->link_tubes[i]], 0);
		turns[i].turn = 1;
		i++;
	}
}

t_bool			browse_map(t_data *data)
{
	t_turn	*turns;
	UINT	nbr_col;
	t_list	*paths;

	if (!(turns = init_turn(data->tubes)))
		return (false);
	nbr_col = get_nbr_columns(data->r_tab[0], data->r_tab[1]);
	start_columns(nbr_col, &data->r_tab[0], data->t_tab, turns);
	recursive_bs_turn(data, turns, data->r_tab[0].nb_link_tubes, 2);
	paths = get_id_path_list(data->r_tab[1], data);
//	stock_rooms_to_go(paths, data);
	free(turns);
	return (true);
}
