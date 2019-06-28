/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lib_plus.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 18:12:13 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 15:02:02 by matheme     ###    #+. /#+    ###.fr     */
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

long	ft_atol_modify(const char *str, t_bool *boule)
{
	int		i;
	int		neg;
	long	result;

	neg = 1;
	result = 0;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	str = &str[i];
	i = -1;
	while (str[++i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i] - '0';
	if (str[i] != ' ' && str[i] != '\0')
		*boule = false;
	return (result * neg);
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

long	atol_id(const char *s, char c, UINT index, t_bool *boule)
{
	long i;

	i = 0;
	while (s[i] && index)
	{
		while (s[i] && s[i] != c)
			i++;
		index -= 1;
		i++;
	}
	return (ft_atol_modify(&s[i], boule));
}

ULL		bin(char c)
{
    const ULL tab[64] = {
        0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,
        32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304,
        8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912,
        1073741824, 2147483648, 4294967296, 8589934592, 17179869184,
        34359738368, 68719476736, 137438953472, 274877906944, 549755813888,
        1099511627776, 2199023255552, 4398046511104, 8796093022208,
        17592186044416, 35184372088832, 70368744177664, 140737488355328,
        281474976710656, 562949953421312, 0x4000000000000, 0x8000000000000,
        0x10000000000000, 0x20000000000000, 0x40000000000000, 0x80000000000000,
        0x100000000000000, 0x200000000000000, 0x400000000000000,
        0x800000000000000, 0x1000000000000000, 0x2000000000000000,
        0x4000000000000000
    };
    return (tab[c]);
}
