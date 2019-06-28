/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/13 12:46:11 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/25 18:53:35 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	biggest_tab(UINT **tab)
{
	UINT i;
	UINT ret;

	ret = tab[0][1];
	if (tab[1] == NULL)
		return ;
	i = 1;
	while (tab[i])
	{
		if ()
	}
}

UINT	get_line_num(t_data data)
{
	ULL ret;
	UINT div;
	UINT mod;

	ret = 0;
	div = data->ants / data->path_nbr;
	mod = data->ants % data->path_nbr;
	FPF("div = %U mod = %u\n", div, mod);
	ret = div * biggest_tab(data->ret) + mod * biggest_tab_left(data->ret);
	return (ret);
}
char	*fill_output(t_data *data)
{
	char *buf;
	UINT ants;
	UINT ctab;

	UINT t1 = 0;

	ants = data->ants;
	buf = ft_strnew(BUF_SIZE);
	while (ants)
	{
		ctab = 0;
		while (data->ret[ctab++])
		{
			fill_line(data, ctab, ants--, buf);
			FPF("ctab = %u ants = %u iteration = %u\n", ctab, ants, t1++);
		}
	}
}

/* ne pas oublier de faire l opti pour la detection de la combinaison des plus 
 * courts chemins (ex 2 chemins a 2 lenght et 1 a 500) */
