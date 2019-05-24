/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_skip.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:30:21 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 15:47:44 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	skip_ants_number(char *s)
{
	scan_line_line(s);
}

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
