/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_is_order.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 16:22:26 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 18:23:09 by matheme     ###    #+. /#+    ###.fr     */
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
**		0 NO it's not an Order
**		1 OK it's start order
**		2 OK it's end Order
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
