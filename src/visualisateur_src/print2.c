/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/24 16:02:11 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 16:06:17 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	show_name_room(t_env *env, t_data data)
{
	UINT	i;
	void	*mlx;
	void	*win;
	int		clr;
	double	mult;

	mult = env->zoom + env->marge;
	mlx = env->mlx_ptr;
	win = env->win_ptr;
	clr = 0x63FC00;
	i = 0;
	while (i < data.rooms)
	{
		mlx_string_put(mlx, win, data.r_tab[i].x * mult + env->y_img +
		env->marge / 2, data.r_tab[i].y * mult + env->x_img + env->marge / 2,
			clr, data.r_tab[i].name);
		i++;
	}
}
