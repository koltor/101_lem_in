/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_get_room.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 16:20:52 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 17:32:49 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	split_line_for_room(char *line, t_room *room)
{
	if (!(room->name = ft_strsub_c(line, ' ')))
	{
		f_error(ERR_MALLOC, NULL);
		return (false);
	}
	room->x = atoi_id(line, ' ', 1);
	room->y = atoi_id(line, ' ', 2);
	return (true);
}

static t_bool	select_ben(char *line, t_data *data, int *order, UINT *ir)
{
	if (*order == 1)
	{
		if (split_line_for_room(line, &data->r_tab[0]))
			return (false);
	}
	else if (*order == 2)
	{
		if (split_line_for_room(line, &data->r_tab[1]))
			return (false);
	}
	else if (*order == 0 && *ir < data->rooms)
	{
		if (split_line_for_room(line, &data->r_tab[*ir]))
			return (false);
	}
	*ir = (*order == 0) ? *ir + 1 : *ir;
	*order = 0;
	return (true);
}

char			*get_room(char *file_line, t_data *data)
{
	char	*line;
	UINT	ir;
	int		order;
	char	type;

	ir = 2;
	order = 0;
	skip_ants_number(file_line);
	while ((line = scan_line_line(file_line)))
	{
		if ((type = is_room(line)) == -1)
			break ;
		if (type == 1 && order == 0 && (order = is_order(line)))
			continue ;
		if (type == 0)
			if (select_ben(line, data, &order, &ir))
				return (NULL);
	}
	if (data->r_tab[0].name == NULL || data->r_tab[1].name == NULL)
	{
		data->r_tab[0].name == NULL ? f_error(ERR_LACK_BEGIN, NULL) : 0;
		data->r_tab[1].name == NULL ? f_error(ERR_LACK_END, NULL) : 0;
		return (NULL);
	}
	return (line);
}
