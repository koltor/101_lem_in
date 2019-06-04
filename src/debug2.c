/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/04 22:18:29 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/04 22:18:57 by matheme     ###    #+. /#+    ###.fr     */
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

void			debug_main(int option)
{
	char d;

	d = *(char*)f_error(0, NULL);
	dprintf(1, "     option: %d                Error: %d\n", option, (int)d);
	str_error((int)d);
}
