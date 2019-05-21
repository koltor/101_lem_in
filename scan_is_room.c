/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_room.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:45:14 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 16:46:12 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

char	is_room(const char *s)
{
	UINT i;

	i = 0;
	if (*s == '#')
		return (false);
	if (!s[i] || s[i] == ' ')
		return (-1);
	while (s[i] && s[i] != ' ')
		i++;
	if (!s[i] || s[i++] != ' ')
		return (-1);
	if (s[i] && s[i] == ' ')
		return (-1);
	while (s[i] && s[i] != ' ')
		i++;
	if (!s[i] || s[i++] != ' ')
		return (-1);
	if (s[i] && s[i] == ' ')
		return (-1);
	while (s[i] && s[i] != ' ')
		i++;
	if (s[i])
		return (-1);
	return (true);
}
