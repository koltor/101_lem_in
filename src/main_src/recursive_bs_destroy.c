/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recursive_bs_destroy.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/05 17:40:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/13 15:03:34 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	destroy_turn(t_turn *turns, UINT old_children, UINT id_turn, UINT child)
{
	UINT ipath;

	ipath = turns[id_turn].id_path;
	while (++id_turn < old_children + child)
	{
		if (turns[id_turn].id_path == ipath)
			turns[id_turn].turn = 0;
	}
	return (child);
}
