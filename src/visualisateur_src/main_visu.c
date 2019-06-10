/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_visu.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/31 11:05:47 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/10 16:47:01 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

/*
** main_visualisateur:
**	this is the main of the vizualiseur
**	init all the strcut env and open the windown and the event
**	parameters
**		the stuct data
*/

void		main_visualisateur(t_data data)
{
	t_env		env;
	double		zoom;
	int			marge;
	const char	*name = "visualisateur pour lem_in v1.0 by matheme-ocrossi";

	env.mlx_ptr = mlx_init();
	env.win_ptr = mlx_new_window(env.mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y,
																(char*)name);
	env.img_ptr = mlx_new_image(env.mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	env.img_str = mlx_get_data_addr(env.img_ptr, &env.bpp, &env.s_l,
																&env.endian);
	env.marge = 4;
	env.speedo = 3;
	env.zoom = 50;
	env.help = false;
	env.highlight_path = false;
	env.x_img = WIN_SIZE_X / 4;
	env.y_img = WIN_SIZE_Y / 4;
	env.data = &data;
	mlx_hook(env.win_ptr, 2, 1, keyboard_events, &env);
	mlx_mouse_hook(env.win_ptr, mouse_events, &env);
	put_img(&env, *(env.data));
	mlx_loop(env.mlx_ptr);
}
