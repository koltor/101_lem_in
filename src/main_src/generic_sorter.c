/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generic_sorter.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 19:00:29 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/22 11:05:28 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	generic_sorter(t_data *data) // ! cas p
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
	FPF("\n===================================================\n");
//	print_cp_tab_binary(data);
	FPF("\n===================================================\n");
	if (sort_opti2(data))
	{
		FPF("opti path bug\n");
		return (0);
	}
//	FPF("\n===================================================\n");
//	print_cp_tab_binary(data);
//	FPF("nombre de fourmis a faire passer %u\n", data->ants);
//	FPF("\n===================================================\n");
//
//	print_comp_tab(data);
	return (1);
}
