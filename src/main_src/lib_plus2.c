/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lib_plus2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/26 18:00:14 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 17:14:44 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ft_strlenc:
**	parameters
**		need a string
**		need a stopping char
**	variables
**		UINT for moving on the string
**	return value
**		the number of char untill stopping char
*/

size_t	ft_strlenc(const char *s, char c)
{
	UINT i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/*
** ft_strsub_c:
**	parameters
**		need a string
**		need a stopping char
**	return value
**		a new string corresponding at the first part of a
**		string split with stopping char
*/

char	*ft_strsub_c(const char *src, char c)
{
	return (ft_strsub(src, 0, ft_strlenc(src, c)));
}

/*
** ft_revstrsub_c:
**	parameters
**		need a string
**		need a stopping char
**	return value
**		a new string corresponding at the last part of a
**		string split with stopping char
*/

char	*ft_revstrsub_c(const char *src, char c)
{
	return (ft_strsub(src, ft_strlenc(src, c) + 1, ft_strlen(src)));
}
