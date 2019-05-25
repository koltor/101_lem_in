/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_room.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:42:37 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/23 21:33:16 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** get_number_of_room:
**	parameters
**		need a string containing a line of the file
**	variables
**		INT		for stock the number of ants after scaning
**		s_cpy	for copy the string S give at argument
**		line	stock temporately the reading line after call scan_line_line
**		ret		keep the return of the function IS_ROOM
**	return value
**		the number of rooms and affect an error of a problem as occurd
*/

UINT	get_number_of_room(const char *s)
{
	UINT	nb_room;
	char	*s_cpy;
	char	*line;
	char	ret;

	nb_room = 0;
	if (!(s_cpy = ft_strdup(s)))
		return (*(UINT*)f_error(ERR_MALLOC, &nb_room));
	skip_ants_number(s_cpy);
	while ((line = scan_line_line(s_cpy)))
	{
		if ((ret = is_room(line)) == 0)
			nb_room += 1;
		else if (ret == -1)
			break ;
	}
	scan_line_line(NULL);
	free(s_cpy);
	if (nb_room < 2)
		f_error(ERR_ROOMS, NULL);
	return (nb_room);
}
