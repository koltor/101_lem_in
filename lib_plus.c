/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lib_plus.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 18:12:13 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 19:46:37 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

size_t	ft_strlenc(const char *s, char c)
{
	UINT i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*ft_strsub_c(const char *src, char c)
{
	return (ft_strsub(src, 0, ft_strlenc(src, c)));
}

int		atoi_id(const char *s, char c, UINT index)
{
	int i;

	i = 0;
	while (s[i] && index)
	{
		while (s[i] != c && index)
			i++;
		index -= 1;
	}
	return (ft_atoi(&s[i]));
}
