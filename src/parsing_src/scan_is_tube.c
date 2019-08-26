/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_is_tube.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:45:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/18 22:21:19 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** is_Tube:
**	parameters
**		need a string containing a line of the file
**	variables
**		UINT for moving on the string
**		UINT for keep a back position
**	return value
**		0 OK it's a Tube
**		1 NO it's a Comment
**		-1 NO it's not a Tube
*/

int		is_tube(const char *s)
{
	int		j;
	t_bool	ok;

	ok = false;
	j = 0;
	if (*s == '#')
		return (1);
	while (s[j])
	{
		if (s[j] == ' ')
			return (-1);
		if (s[j] == '-')
			ok = true;
		j++;
	}
	if (ok == false || j == 0)
		return (-1);
	if (s[j - 1] == '-')
		return (-1);
	return (0);
}
