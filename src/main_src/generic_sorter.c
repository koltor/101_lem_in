/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generic_sorter.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 19:00:29 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/12 16:50:55 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	generic_sorter(t_data *data)
{
	if (init_stocker_tab(data))
	{
		FPF("init stocker bug\n");
		return (0);
	}
	if (fill_comp_tab(data))
	{
		FPF("fill comp tab bug\n");
		return (0);
	}
	print_cp_tab_binary(data);
	return (1);
}
