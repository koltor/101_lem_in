/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/31 11:48:01 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/31 17:34:24 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

int				fill_pixel(t_env *env, int x, int y)
{
	int pos;

	pos = WIN_SIZE_X * (y + env->x_img) * 4 + (x + env->y_img) * 4;
	if (pos >= 0 && pos < WIN_SIZE_X * WIN_SIZE_Y * 4 &&
		(x + env->y_img) < WIN_SIZE_X * 4 && (x + env->y_img) >= 0 &&
		(x + env->y_img) < WIN_SIZE_X)
	{
		(env->img_str)[pos + 2] = env->color / 256 / 256;
		(env->img_str)[pos + 1] = env->color / 256;
		(env->img_str)[pos] = env->color % 256;
		return (0);
	}
	return (1);
}

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

static void		put_tubes(UINT size, t_room *r_tab, t_tube *t_tab, t_env *env)
{
	double index[4];
	double mult;

	mult = env->zoom + env->marge;
	env->color = 0x5E450E;
	while (--size)
	{
		index[0] = r_tab[t_tab[size].salle2].x * mult + mult / 2;
		index[1] = r_tab[t_tab[size].salle2].y * mult + mult / 2;
		index[2] = r_tab[t_tab[size].salle1].x * mult + mult / 2;
		index[3] = r_tab[t_tab[size].salle1].y * mult + mult / 2;
		algo_bresenham(index, env);
	}
	index[0] = r_tab[t_tab[size].salle2].x * mult + mult / 2;
	index[1] = r_tab[t_tab[size].salle2].y * mult + mult / 2;
	index[2] = r_tab[t_tab[size].salle1].x * mult + mult / 2;
	index[3] = r_tab[t_tab[size].salle1].y * mult + mult / 2;
	algo_bresenham(index, env);
}

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
	user_interface(*env);
}
