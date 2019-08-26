/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_check_tube.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/28 16:07:23 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 18:02:12 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void		check_duplicate_tube(t_tube *t_tab, UINT size)
{
	UINT	i;
	UINT	j;
	t_tube	tube;

	i = 0;
	while (i < size)
	{
		tube = t_tab[i];
		j = i + 1;
		while (j < size)
		{
			if ((tube.salle1 == t_tab[j].salle1 &&
				tube.salle2 == t_tab[j].salle2) ||
				(tube.salle1 == t_tab[j].salle2 &&
				tube.salle2 == t_tab[j].salle1))
			{
				f_error(ERR_DUPL_TUBE, NULL);
				return ;
			}
			j += 1;
		}
		i += 1;
	}
}
