/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_is_tube.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:45:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/23 21:45:50 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		is_tube(const char *s)
{
	UINT i;
	UINT j;

	i = 0;
	if (*s == '#')
		return (1);
	if (!s[i] || s[i] == ' ')
		return (-1);
	while (s[i] && s[i] != '-')
	{
		if (s[i++] == ' ')
			return (-1);
	}
	j = i;
	if (!s[i] || i == 0)
		return (-1);
	while (s[i])
	{
		if (s[i++] == ' ')
			return (-1);
	}
	if (j == i)
		return (-1);
	return (0);
}
