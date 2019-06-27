/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_get_room.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 20:11:39 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 17:11:44 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

static t_bool	check_duplicate_room_se(UINT id, t_room *r_tab, UINT st, UINT size)
{
	char	d;
	t_bool	ret;
	t_room room;

	ret = false;
	room = r_tab[id];
	d = room.name[1];
	st--;
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
	size = (id == 1) ? 0 : 1;
	if (!r_tab[size].name)
		return (true);
	if (room.x == r_tab[size].x && room.y == r_tab[size].y)
		return (*(t_bool*)f_error(ERR_DUPL_XY_ROOM, &ret));
	if (d != r_tab[size].name[1])
		return (true);
	if (!ft_strcmp(room.name, r_tab[size].name))
		return (*(t_bool*)f_error(ERR_DUPL_ROOM, &ret));
	return (true);
}

static t_bool	check_duplicate_room_g(t_room room, t_room *r_tab, UINT st, UINT size)
{
	char	d;
	t_bool	ret;

	ret = false;
	d = room.name[1];
	st--;
	while (++st < size)
	{
		if (room.x == r_tab[st].x && room.y == r_tab[st].y)
			return (*(t_bool*)f_error(ERR_DUPL_XY_ROOM, &ret));
		if (d != r_tab[st].name[1])
			continue ;
		if (!ft_strcmp(room.name, r_tab[st].name))
			return (*(t_bool*)f_error(ERR_DUPL_ROOM, &ret));
	}
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

/*
** split_line_for_room:
**	parameters
**		need a line of the file
**		need a case of the room_tab
**	return value
**		true of the data is collect
**		false otherwise
*/

static t_bool	split_line_for_room(char *line, t_room *room)
{
	long	x1;
	long	y1;
	t_bool	value;

	value = false;
	if (line && *line == 'L')
		return (*(t_bool*)f_error(ERR_ROOM_FORMAT, &value));
	if (!(room->name = ft_strsub_c(line, ' ')))
		return (*(t_bool*)f_error(ERR_MALLOC, &value));
	x1 = atol_id(line, ' ', 1);
	y1 = atol_id(line, ' ', 2);
	if (x1 < -2147483648 || y1 < -2147483648 ||
		x1 > 2147483647 || y1 > 2147483647)
		return (*(t_bool*)f_error(ERR_OVERFLOW, &value));
	room->x = (int)x1;
	room->y = (int)y1;
	return (true);
}

/*
** reset_one_room:
**	reset a room
**	parameters
**		need a room to reset
**	return value
**		false
*/

static t_bool	reset_one_room(t_room *room)
{
	if (room->name)
	{
		free(room->name);
		room->name = NULL;
	}
	room->x = 0;
	room->y = 0;
	return (false);
}

/*
** select_ben (begin-end-normal):
**	parameters
**		need a line
**		need the struct data
**		need the type of line
**		need an & id for moving it
**	return value
**		true of the data is collect
**		false otherwise
*/

static t_bool	select_ben(char *line, t_data *data, int *order, UINT (*abc)[128])
{
	t_bool	value;
	UINT	id;
	UINT	start;

	value = false;
	start = data->abc.abc_start[line[0]];
	if (*order == 0)
	{
		id = (*abc)[line[0]]++;
		if (split_line_for_room(line, &data->r_tab[id]))
			return (false);
		if (check_duplicate_room_g(data->r_tab[id], data->r_tab, start, id))
			return (reset_one_room(&data->r_tab[id]));
	}
	else
	{
		if (data->r_tab[0].name != NULL && *order == 1)
			return (*(t_bool*)f_error(ERR_DUPLICATE_STR, &value));
		if (data->r_tab[1].name != NULL && *order == 2)
			return (*(t_bool*)f_error(ERR_DUPLICATE_END, &value));
		if (split_line_for_room(line, &data->r_tab[*order - 1]))
			return (false);
		//if (check_duplicate_room_se(*order - 1, data->r_tab, start, id))
		//	return (reset_one_room(&data->r_tab[*order - 1]));
	}
	*order = 0;
	return (true);
}

void			get_room_thread_main(char *file_line, t_data *data, t_thread thread)
{
	char	*line;
	UINT	(*abc_id)[128];
	UINT	cpt;
	int		order;
	char	type;

	abc_id = &data->abc.abc_id;
	order = 0;
	cpt = 0;
	type = 0;
	while (cpt < thread.section || (thread.id == NB_THREAD && type != -1))
	{
		line = scan_line_line_for_threading(file_line, thread.id - 1);
		if ((type = is_room(line)) == -1)
			break ;
		if (type == 1 && order == 0 && (order = is_order(line)))
			continue ;
		if (type == 0)
		{
			if (order == 0)
				cpt++;
			if (select_ben(line, data, &order, abc_id))
				return ;
		}
	}
}
