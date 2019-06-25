/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_get_anthill.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/27 11:54:31 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/25 18:15:37 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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
		scan_line_line(NULL);
		return (false);
	}
	get_tube(file_line, data, line);
	scan_line_line(NULL);
	if (get_nodes(data))
		return (false);
	return (true);
}
