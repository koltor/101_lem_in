/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_get_anthill.c                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 19:59:54 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 19:19:28 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

t_bool	stock_anthill_for_threading(char *file_line, t_data *data)
{
	char *line;

	if (!(data->ants = get_number_of_ants(file_line)))
	{
		data->tubes = 0;
		data->rooms = 0;
		return (false);
	}
	if (multithread_get_room(file_line, data))
	{
		data->tubes = 0;
		return (false);
	}
	multithread_get_tube(file_line, data);
	if (multithreading_get_nodes(data))
		return (false);
	return (true);
}