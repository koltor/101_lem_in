/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_other.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:41:19 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 15:08:26 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** skip_first_comment:
**	a tiny function to quit the function get_number_of_ants properly
**	return value
**		the number of ants and affect an error if necessary
*/

static UINT	exit_get_nb_of_ant(char *line, UINT ants_number, char error)
{
	free(line);
	scan_line_line(NULL);
	return (*(UINT*)(f_error(error, &ants_number)));
}

/*
** skip_first_comment:
**	parameters
**		need a string containing the file_line
**	variables
**		line for stock a line of the file
**	return value
**		the first line who is not a comment
*/

static char	*skip_first_comment(char *s_cpy)
{
	char	*line;
	int		ret;

	while ((line = scan_line_line(s_cpy)))
	{
		if (!line)
			return (NULL);
		if ((ret = is_room(line)) != 1)
			break ;
	}
	return (line);
}

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

UINT		get_number_of_ants(const char *s)
{
	long	ants_number;
	char	*line;
	char	*s_cpy;

	ants_number = 0;
	if (!(s_cpy = ft_strdup(s)))
		return (*(UINT*)f_error(ERR_MALLOC, &ants_number));
	if (!(line = skip_first_comment(s_cpy)))
		return (exit_get_nb_of_ant(s_cpy, ants_number, ERR_OCCURD));
	if (ft_strchr(line, ' '))
		return (exit_get_nb_of_ant(s_cpy, ants_number, ERR_ANTS_SPACE));
	ants_number = ft_atol(line);
	if (ants_number <= 0 || ants_number >= (long)2147483648)
	{
		ants_number = 0;
		return (exit_get_nb_of_ant(s_cpy, ants_number, ERR_ANTS));
	}
	return (exit_get_nb_of_ant(s_cpy, ants_number, -1));
}
