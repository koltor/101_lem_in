/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_is_room.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:45:14 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 15:48:08 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** count_not_space:
**	parameters
**		need a string containing a line of the file
**		UINT adresse for moving on the string
**	variables
**		nb: count the number of char
**	return value
**		the number of space
*/

static int	count_space(const char *s, UINT *i)
{
	int nb;

	nb = 0;
	while (s[*i] && s[*i] == ' ')
	{
		*i += 1;
		nb += 1;
	}
	return (nb);
}

/*
** count_not_space:
**	parameters
**		need a string containing a line of the file
**		UINT adresse for moving on the string
**	variables
**		nb: count the number of char
**	return value
**		the number of char diffent of space
*/

static int	count_not_space(const char *s, UINT *i)
{
	int nb;

	nb = 0;
	while (s[*i] && s[*i] != ' ')
	{
		*i += 1;
		nb += 1;
	}
	return (nb);
}

/*
** is_room:
**	parameters
**		need a string containing a line of the file
**	variables
**		just a UINT for moving on the string
**	return value
**		0 OK it's a Room
**		1 NO it's a Comment
**		2 NO it's not a Room
*/

int			is_room(const char *s)
{
	UINT i;

	i = 0;
	if (*s == '#')
		return (1);
	if (count_space(s, &i) != 0)
		return (-1);
	if (count_not_space(s, &i) == 0)
		return (-1);
	if (count_space(s, &i) != 1)
		return (-1);
	if (count_not_space(s, &i) == 0)
		return (-1);
	if (count_space(s, &i) != 1)
		return (-1);
	if (count_not_space(s, &i) == 0)
		return (-1);
	if (s[i])
		return (-1);
	return (0);
}
