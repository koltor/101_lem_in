/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_create_struct.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:27:14 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 19:23:44 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** create_room:
**	parameters
**		need the number of room to allocate
**	variables
**		just an address
**	return value
**		return the first address of the room_table
*/

t_room	*create_room(UINT size)
{
	t_room	*room_tab;

	if (!(room_tab = malloc(sizeof(t_room) * size)))
		return (f_error(ERR_MALLOC, NULL));
	while (size--)
	{
		room_tab[size].tubes = NULL;
		room_tab[size].name = NULL;
		room_tab[size].x = 0;
		room_tab[size].y = 0;
	}
	return (room_tab);
}

/*
** free_room:
**	parameters
**		need the room_table to free
**		need the size of the table
**	variables
**		just an address
**	return value
**		return the first address of the room_table
*/

void	free_room(t_room *r_tab, UINT size)
{
	UINT i;

	i = 0;
	while (i < size)
	{
		if (r_tab[i].name)
			free(r_tab[i].name);
		i++;
	}
	free(r_tab);
}

/*
** create_tube:
**	parameters
**		need the number of tube to allocate
**	variables
**		just an address
**	return value
**		return the first address of the tube_table
*/

t_tube	*create_tube(UINT size)
{
	t_tube	*tube_tab;

	if (!(tube_tab = malloc(sizeof(t_tube) * size)))
		return (f_error(ERR_MALLOC, NULL));
	while (size--)
	{
		tube_tab[size].salle1 = 0;
		tube_tab[size].salle2 = 0;
		tube_tab[size].path_id = 0;
	}
	return (tube_tab);
}
