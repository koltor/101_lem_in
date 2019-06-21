/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread.skip.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 15:46:22 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 17:10:44 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

/*
** skip_ants_number:
**	parameters
**		need a string containing a line of the file
**	skip a line of the line S
*/

t_bool	skip_ants_number_for_threading(char *s, UINT id)
{
	char *line;

	if (!(line = scan_line_line_for_threading(s, id)))
	{
		f_error(ERR_ONLY_COMMENT, NULL);
		return (false);
	}
	while (is_room(line) == 1)
	{
		if (is_order(line))
		{
			f_error(ERR_ONLY_COMMENT, NULL);
			return (false);
		}
		if (!(line = scan_line_line_for_threading(s, id)))
		{
			f_error(ERR_ONLY_COMMENT, NULL);
			return (false);
		}
	}
	return (true);
}

/*
** skip_room:
**	parameters
**		need a string containing a line of the file
**	variables
**		line stock temporately the reading line after call scan_line_line
**	return value
**		the first line not corresponding with the pattern ROOM
*/

char	*skip_room_for_multithreading(char *s, UINT id)
{
	char *line;

	while ((line = scan_line_line_for_threading(s, id)))
	{
		if (is_room(line) == -1)
			break ;
	}
	return (line);
}