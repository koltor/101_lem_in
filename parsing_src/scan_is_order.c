/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_is_order.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 16:22:26 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 18:35:18 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** is_order:
**	parameters
**		need a string containing a line of the file
**	variables
**		just a UINT for moving on the string
**	return value
**		0 OK it's a Order
**		1 NO it's a Comment
**		2 NO it's not a Order
*/

int		is_order(const char *s)
{
	if (s && s[0] != '#')
		return (0);
	if (!strcmp(s, "##start"))
		return (1);
	if (!strcmp(s, "##end"))
		return (2);
	return (0);
}
