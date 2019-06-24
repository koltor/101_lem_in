/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/31 11:48:01 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 16:04:41 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

/*
** draw_cube:
**	allows the possibility to draw a cube
**	parameters
**		need the struct env
**		the x of the origin pixel
**		the y of the origin pixel
**		the zoom corresponding of the length of the cube
**	variables
**		index[4] need to pass the x and y in bresenham
*/

static void		draw_cube(double x, double y, double zoom, t_env *env)
{
	double index[4];

	index[0] = x + zoom;
	index[1] = y;
	index[2] = x;
	index[3] = y;
	algo_bresenham(index, env);
	index[0] = x;
	index[1] = y + zoom;
	index[2] = x;
	index[3] = y;
	algo_bresenham(index, env);
	index[0] = x + zoom;
	index[1] = y + zoom;
	index[2] = x;
	index[3] = y + zoom;
	algo_bresenham(index, env);
	index[0] = x + zoom;
	index[1] = y + zoom;
	index[2] = x + zoom;
	index[3] = y;
	algo_bresenham(index, env);
}

/*
** put_rooms:
**	allows the possibility to put the differents room in the img
*/

static void		put_rooms(UINT size, t_room *r_tab, t_env *env)
{
	double mult;

	mult = env->zoom + env->marge;
	env->color = 0xffffff;
	while (--size)
	{
		if (size == 1)
			env->color = 0xff0000;
		draw_cube(r_tab[size].x * mult, r_tab[size].y * mult, env->zoom, env);
	}
	env->color = 0x00ff00;
	draw_cube(r_tab[size].x * mult, r_tab[size].y * mult, env->zoom, env);
}

/*
** select_color_tube:
**	allows the possibility to select the color
**	parameters
**		UINT value
**		the struct env
**	variables
**		color_tab[~] is a bibliotheque of color
*/

static void		select_color_tube(t_env *env, UINT value)
{
	const int color_tab[18] = {
		0x5E450E,
		0xFF8B00,
		0xE1FF6A,
		0x33FFFA,
		0x3338FF,
		0xF933FF,
		0x5E450E,
		0x5E450E,
		0x5E450E,
		0x5E450E,
		0x5E450E,
		0x5E450E,
		0x5E450E,
		0x5E450E,
		0x5E450E,
		0x5E450E,
		0x5E450E,
		0x5E450E
	};

	if (!env->highlight_path)
		env->color = (value >= 18) ? 0x888888 : color_tab[value];
	else
		env->color = 0x5E450E;
}

/*
** put_tubes:
**	allows the possibility to put the differents tubes in the img
*/

static void		put_tubes(UINT size, t_room *r_tab, t_tube *t_tab, t_env *env)
{
	double index[4];
	double mult;

	mult = env->zoom + env->marge;
	while (--size)
	{
		select_color_tube(env, t_tab[size].path_id);
		index[0] = r_tab[t_tab[size].salle2].x * mult + mult / 2;
		index[1] = r_tab[t_tab[size].salle2].y * mult + mult / 2;
		index[2] = r_tab[t_tab[size].salle1].x * mult + mult / 2;
		index[3] = r_tab[t_tab[size].salle1].y * mult + mult / 2;
		algo_bresenham(index, env);
	}
	select_color_tube(env, t_tab[size].path_id);
	index[0] = r_tab[t_tab[size].salle2].x * mult + mult / 2;
	index[1] = r_tab[t_tab[size].salle2].y * mult + mult / 2;
	index[2] = r_tab[t_tab[size].salle1].x * mult + mult / 2;
	index[3] = r_tab[t_tab[size].salle1].y * mult + mult / 2;
	algo_bresenham(index, env);
}

/*
** put_img:
** it's the main of the calcul of the img
** exectute the differents functions who need to calcul the image
*/

void			put_img(t_env *env, t_data data)
{
	mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	env->img_ptr = mlx_new_image(env->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	mlx_get_data_addr(env->img_ptr, &env->bpp, &env->s_l, &env->endian);
	env->img_str = mlx_get_data_addr(env->img_ptr, &(env->bpp),
											&(env->s_l), &(env->endian));
	put_rooms(data.rooms, data.r_tab, env);
	put_tubes(data.tubes, data.r_tab, data.t_tab, env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	if (env->zoom >= 20)
		show_name_room(env, data);
	user_interface(*env);
}
