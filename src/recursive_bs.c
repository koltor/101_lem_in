/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recursive_bs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/30 14:38:15 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/04 14:50:21 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	lap_room_managment(t_tube *tubes, t_room *room, t_turn *turns, UINT current_turn, UINT id_turn, UINT nbr_leads)
{
	UINT i;
	UINT new_turn;

	i = 0;
	new_turn = 0;
	while (i < room->nb_link_tubes)
	{
		if (tubes[room->link_tubes[i]].path_id == 0 && (tubes[room->link_tubes[i]].salle1 != 1 && tubes[room->link_tubes[i]].salle2 != 1))
		{
		/*	if (tubes[room->link_tubes[i]].salle1 == 1 || tubes[room->link_tubes[i]].salle2 == 1)
			{
				new_turn += 1;
				break ;
			}*/
		//	dprintf(1, "tarace i = %d\n", i);
			tubes[room->link_tubes[i]].path_id = turns[id_turn].id_path;
			tubes[room->link_tubes[i]].turn = current_turn;
			turns[nbr_leads + new_turn].id_path = turns[id_turn].id_path;
			turns[nbr_leads + new_turn].index_turn = current_turn;
			turns[nbr_leads + new_turn].id_room = get_id_room(tubes[room->link_tubes[i]], turns[id_turn].id_room);
			new_turn += 1;
		}
/*		else
		{
		}*/
		i++;
	}
	printf("end of lap room managment new_turn = %d\n", new_turn);
	return (new_turn);
}

UINT	lap_managment(t_data *data, t_turn *turns, UINT nbr_leads, UINT current_turn)
{
	UINT i;
	UINT new_turn;

	i = 0;
	new_turn = 0;
	while (i < nbr_leads)
	{
		if (turns[i].index_turn == current_turn - 1)
		{
			new_turn += lap_room_managment(data->t_tab, &data->r_tab[turns[i].id_room], turns, current_turn, i, nbr_leads);
			printf("dans le while de LM on a turns[i].id_room == %d\n", turns[i].index_turn);
		}
		if (turns[i].id_room == 1)
		{
			dprintf(1, "hey\n");
			break ;
		}
		i++;
	}
	printf("end of LAP managment new_turn = %d\n", new_turn);
	return (new_turn);
}

void	recursive_bs_turn(t_data *data, t_turn *turns, UINT nbr_leads, UINT lap)
{
	UINT children;

	children = lap_managment(data, turns, nbr_leads, lap);
	if (children)
		recursive_bs_turn(data, &turns[nbr_leads], children, ++lap);
}
