/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_anthill_diese.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 15:39:09 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 15:51:33 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** manage_diese
**	parameters
**		need a string containing the information
**		THE binary checker SE
** if the ligne of information begin by #
** this function is call ad change the value of SE if the order
** ##start or ##end is call
*/

t_bool	manage_diese(const char *s, char *se)
{
	if (!strcmp(s, "##start"))
	{
		if (*se & 1)
			return (false);
		*se = *se | 1;
	}
	else if (!strcmp(s, "##end"))
	{
		if (*se & 2)
			return (false);
		*se = *se | 2;
	}
	return (true);
}
