/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_skip.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:30:21 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 16:51:07 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** skip_ants_number:
**	parameters
**		need a string containing a line of the file
**	skip a line of the line S
*/

void	skip_ants_number(char *s)
{
	char *line;

	line = scan_line_line(s);
	while (is_room(line) == 1)
		line = scan_line_line(s);
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

char	*skip_room(char *s)
{
	char *line;

	while ((line = scan_line_line(s)))
	{
		if (is_room(line) == -1)
			break ;
	}
	return (line);
}
