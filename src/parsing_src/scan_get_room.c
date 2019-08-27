/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_get_room.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 16:20:52 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 18:01:49 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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
	room->len_name = ft_strlen(room->name);
	value = true;
	x1 = atol_id(line, ' ', 1, &value);
	y1 = atol_id(line, ' ', 2, &value);
	if (value == false)
		return (*(t_bool*)f_error(ERR_ROOM_WRONG_POS, &value));
	value = false;
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

static t_bool	select_ben(char *line, t_data *data, int *ord, UINT (*abc)[128])
{
	t_bool	value;
	UINT	id;
	UINT	start;

	id = (*ord == 0) ? (*abc)[line[0]]++ : (*abc)[line[0]];
	if ((value = false) && id == data->rooms && *ord == 0)
		return (false);
	if ((start = data->abc.abc_start[line[0]]) && *ord == 0)
	{
		if (split_line_for_room(line, &data->r_tab[id]))
			return (false);
		if (check_dup_room_g(data->r_tab[id], data->r_tab, start, id))
			return (reset_one_room(&data->r_tab[id]));
		return (true);
	}
	if (data->r_tab[0].name != NULL && *ord == 1)
		return (*(t_bool*)f_error(ERR_DUPLICATE_STR, &value));
	if (data->r_tab[1].name != NULL && *ord == 2)
		return (*(t_bool*)f_error(ERR_DUPLICATE_END, &value));
	if (split_line_for_room(line, &data->r_tab[*ord - 1]))
		return (false);
	if (check_dup_room_se(*ord - 1, data->r_tab, start, id))
		return (reset_one_room(&data->r_tab[*ord - 1]));
	*ord = 0;
	return (true);
}

/*
** get_room:
**	transform the middle part of the file into room_data
**	parameters
**		the file_line of the file
**		the struct data
**	variable
**		a line to stock the line after call scan_line_line
**		an order to know the order given by an upper line
**		type to know the type of the line
**		an id to move on the room_table
**	return value
**		return the line how the function stop and affect an error
**		if an error occurd
*/

char			*get_room(char *file_line, t_data *data)
{
	char	*line;
	int		order;
	char	type;

	order = 0;
	while ((line = scan_line_line(file_line)))
	{
		if ((type = is_room(line)) == -1)
			break ;
		if (type == 1 && order == 0 && (order = is_order(line)))
			continue ;
		if (type == 1 && order != 0 && is_order(line))
			return (f_error(ERR_ORDER, NULL));
		if (type == 0 && select_ben(line, data, &order, &data->abc.abc_id))
			break ;
	}
	if (*(char*)f_error(0, NULL) != 0)
		return (NULL);
	if (order)
		return (f_error(ERR_ORDER, NULL));
	if (data->r_tab[0].name == NULL)
		return (f_error(ERR_LACK_BEGIN, NULL));
	else if (data->r_tab[1].name == NULL)
		return (f_error(ERR_LACK_END, NULL));
	return (line);
}
