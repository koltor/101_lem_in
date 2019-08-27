/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_check_room.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/28 16:34:33 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 17:59:25 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	under_check_room(t_room room, t_room *r_tab, UINT st, UINT size)
{
	t_bool	ret;
	char	d;

	ret = false;
	d = room.name[1];
	while (++st < size)
	{
		if (!r_tab[st].name)
			break ;
		if (room.x == r_tab[st].x && room.y == r_tab[st].y)
			return (*(t_bool*)f_error(ERR_DUPL_XY_ROOM, &ret));
		if (d != r_tab[st].name[1])
			continue ;
		if (!ft_strcmp(room.name, r_tab[st].name))
			return (*(t_bool*)f_error(ERR_DUPL_ROOM, &ret));
	}
	return (true);
}

t_bool			check_dup_room_se(UINT id, t_room *r_tab, UINT st, UINT s)
{
	char	d;
	t_bool	ret;
	t_room	room;

	ret = false;
	room = r_tab[id];
	d = room.name[1];
	st--;
	if (under_check_room(room, r_tab, st, s))
		return (false);
	s = (id == 1) ? 0 : 1;
	if (!r_tab[s].name)
		return (true);
	if (room.x == r_tab[s].x && room.y == r_tab[s].y)
		return (*(t_bool*)f_error(ERR_DUPL_XY_ROOM, &ret));
	if (d != r_tab[s].name[1])
		return (true);
	if (!ft_strcmp(room.name, r_tab[s].name))
		return (*(t_bool*)f_error(ERR_DUPL_ROOM, &ret));
	return (true);
}

t_bool			check_dup_room_g(t_room room, t_room *r_tab, UINT st, UINT size)
{
	char	d;
	t_bool	ret;

	ret = false;
	d = room.name[1];
	st--;
	if (under_check_room(room, r_tab, st, size))
		return (false);
	size = 2;
	while (size--)
	{
		if (!r_tab[size].name)
			continue ;
		if (room.x == r_tab[size].x && room.y == r_tab[size].y)
			return (*(t_bool*)f_error(ERR_DUPL_XY_ROOM, &ret));
		if (d != r_tab[size].name[1])
			continue ;
		if (!ft_strcmp(room.name, r_tab[size].name))
			return (*(t_bool*)f_error(ERR_DUPL_ROOM, &ret));
	}
	return (true);
}
