/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_other.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:41:19 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 16:50:12 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** get_number_of_ants:
**	parameters
**		need a string containing a line of the file
**	variables
**		INT for stock the number of ants after scaning
**		s_cpy for copy the string S give at argument
**	return value
**		the number of ants and affect an error of a problem as occurd
*/

UINT	get_number_of_ants(const char *s)
{
	int		ants_number;
	char	*line;
	char	*s_cpy;

	ants_number = 0;
	if (!(s_cpy = ft_strdup(s)))
		return (*(UINT*)f_error(ERR_MALLOC, &ants_number));
	line = scan_line_line(s_cpy);
	while (is_room(line) == 1)
	{
		line = scan_line_line(s_cpy);
		if (!line)
		{
			free(s_cpy);
			scan_line_line(NULL);
			return (*(UINT*)(f_error(ERR_OCCURD, &ants_number)));
		}
	}
	if (ft_strchr(line, ' '))
	{
		scan_line_line(NULL);
		free(s_cpy);
		return (*(UINT*)(f_error(ERR_ANTS_SPACE, &ants_number)));
	}
	ants_number = ft_atoi(line);
	scan_line_line(NULL);
	free(s_cpy);
	if (ants_number <= 0)
		return (*(UINT*)(f_error(ERR_ANTS, &ants_number)));
	return ((UINT)ants_number);
}
