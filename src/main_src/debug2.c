/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/04 22:18:29 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/05 18:12:04 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void			show_turns(t_turn *turns, UINT size)
{
	UINT i;

	i = 0;
	while (i < size)
	{
		dprintf(1, "id_room = %u, id_path = %u, turn_index = %u\n",
					turns[i].id_room, turns[i].id_path, turns[i].turn);
		i++;
	}
}

void			global_info(t_data *data)
{
	dprintf(1, "------------------Information General-----------------\n");
	dprintf(1, "  salle: %-4u       tube: %-4u         fourmis: %-5u\n",
	data->rooms, data->tubes, data->ants);
}

void			debug_main(int option)
{
	char d;

	d = *(char*)f_error(0, NULL);
	dprintf(1, "  option: %d         error: %d\n", option, (int)d);
	str_error((int)d);
}
