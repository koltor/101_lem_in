/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_tube.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:43:14 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 17:54:31 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** get_number_of_tube:
**	parameters
**		need a string containing a line of the file
**	variables
**		INT		for stock the number of ants after scaning
**		s_cpy	for copy the string S give at argument
**		line	stock temporately the reading line after call scan_line_line
**		ret		keep the return of the function IS_ROOM
**	return value
**		the number of tubes and affect an error of a problem as occurd
*/

UINT	get_number_of_tube(const char *s)
{
	UINT	nb_tube;
	char	*s_cpy;
	char	*line;
	char	ret;

	nb_tube = 0;
	if (!(s_cpy = ft_strdup(s)))
		return (*(UINT*)f_error(ERR_MALLOC, &nb_tube));
	skip_ants_number(s_cpy);
	line = skip_room(s_cpy);
	if (line && (ret = is_tube(line)) == 0)
		nb_tube += 1;
	if (line && ret != -1)
	{
		while ((line = scan_line_line(s_cpy)))
			if ((ret = is_tube(line)) == 0)
				nb_tube += 1;
			else if (ret == -1)
				break ;
	}
	scan_line_line(NULL);
	free(s_cpy);
	if (nb_tube < 1)
		f_error(ERR_ROOM_FORMAT, NULL);
	return (nb_tube);
}
