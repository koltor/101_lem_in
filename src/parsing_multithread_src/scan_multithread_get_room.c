/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_get_room.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 20:11:39 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/25 16:37:27 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

static t_bool	check_duplicate_room(UINT id, t_room *r_tab, UINT size, UINT section)
{
	t_bool	ret;
	t_room	room;
	long	i;
	char	c;
	UINT	n;

	ret = false;
	room = r_tab[id];
	c = room.name[0];
	i = -1;
	n = 1;
	while (++i < size)
	{
		if (i != id)
		{
			if(!r_tab[i].name)
			{
				if (i > 1)
					i = section * n++;
				continue ;
			}
			if (room.x == r_tab[i].x && room.y == r_tab[i].y)
				return (*(t_bool*)f_error(ERR_DUPL_XY_ROOM, &ret));
			if (c != r_tab[i].name[0])
				continue ;
			if (!ft_strcmp(room.name, r_tab[i].name))
				return (*(t_bool*)f_error(ERR_DUPL_ROOM, &ret));
		}
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

static t_bool	select_ben(char *line, t_data *data, int *order, UINT *ir, UINT section)
{
	t_bool	value;
	UINT	tmp_id_room;

	value = false;
	if (*order == 0)
	{
		if (*ir >= data->rooms)
			return (false);
		if (split_line_for_room(line, &data->r_tab[*ir]))
			return (false);
		if (check_duplicate_room(*ir, data->r_tab, data->rooms, section))
			return (reset_one_room(&data->r_tab[*ir]));
		*ir = *ir + 1;
	}
	else if (*order == 1 || *order == 2)
	{
		if (data->r_tab[0].name != NULL && *order == 1)
			return (*(t_bool*)f_error(ERR_DUPLICATE_STR, &value));
		if (data->r_tab[1].name != NULL && *order == 2)
			return (*(t_bool*)f_error(ERR_DUPLICATE_END, &value));
		if (split_line_for_room(line, &data->r_tab[*order - 1]))
			return (false);
		if (check_duplicate_room(*order - 1, data->r_tab, data->rooms, section))
			return (reset_one_room(&data->r_tab[*order - 1]));
	}
	*order = 0;
	return (true);
}

void			get_room_thread_main(char *file_line, t_data *data, t_thread thread)
{
	char	*line;
	UINT	ir;
	UINT	cpt;
	int		order;
	char	type;

	ir = (thread.section * (thread.id - 1)) + 2;
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
			if (select_ben(line, data, &order, &ir, thread.section))
			{
				if (thread.thread->rooms >= ir)
					thread.thread->rooms = 0;
				return ;
			}
		}
	}
}
