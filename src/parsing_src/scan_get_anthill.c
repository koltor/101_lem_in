/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_get_anthill.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/27 11:54:31 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 12:11:35 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	free_room_error(t_data *data, UINT nb_room)
{
	UINT i;

	i = 0;
	while (i < nb_room)
	{
		if(data->r_tab[i].name != NULL)
			free(data->r_tab[i].name);
		else if (i == 0 || i == 1)
			nb_room += 1;
		i++;
	}
}

/*
** stock_anthill:
**	parameters
**		need the file_line to recover information about it
**	return value
**		return true if the file_line is in good format
**		and enough information collect
**		otherwise return false
*/

t_bool	stock_anthill(char *file_line, t_data *data)
{
	char *line;

	if (!(data->ants = get_number_of_ants(file_line)))
	{
		data->tubes = 0;
		data->rooms = 0;
		return (false);
	}
	if (!(line = get_room(file_line, data)))
	{
		data->tubes = 0;
		free_room_error(data, data->rooms);
		scan_line_line(NULL);
		return (false);
	}
	if (get_tube(file_line, data, line))
	{
		free_room_error(data, data->rooms);
		data->tubes = 0;
		return (false);
	}
	scan_line_line(NULL);
	if (get_nodes(data))
		return (false);
	return (true);
}
