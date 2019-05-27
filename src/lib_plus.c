/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lib_plus.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 18:12:13 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 15:49:23 by matheme     ###    #+. /#+    ###.fr     */
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

/*
** atoi_id:
**	parameters
**		a string s1
**		a stopping char
**		the number of skipping char c
**	return value
**		a number afer skip a certain number of skipping char
*/

int		atoi_id(const char *s, char c, UINT index)
{
	int i;

	i = 0;
	while (s[i] && index)
	{
		while (s[i] && s[i] != c)
			i++;
		index -= 1;
		i++;
	}
	return (ft_atoi(&s[i]));
}
