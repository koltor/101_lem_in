/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generic_sorter.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 19:00:29 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 11:43:27 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	del_output(t_opt *opt)
{
	UINT i;

	i = 0;
	while (opt->out[i])
	{
		ft_strdel(&(opt->out[i]));
		i++;
	}
	free(opt->out);
}

t_bool	free_tab_turn(t_tube *tab, UINT size)
{
	UINT i;

	i = 0;
	while (i < size)
	{
		free(tab[i].tmp_turn);
		i += 1;
	}
	return (false);
}

UINT	generic_sorter(t_data *data)
{
	if (init_stocker_tab(data))
		return (0);
	if (fill_comp_tab(data))
		return (0);
	if (sort_opti2(data))
		return (0);
	if (new_output(data))
		return (0);
	return (1);
}
