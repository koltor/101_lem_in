/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algo_bresenham.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 10:18:04 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/10 17:57:36 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

static int	algo_bresenham_x(double i[4], t_env *env, double e, double d)
{
	while (i[0] < i[2])
	{
		if (fill_pixel(env, i[0], i[1]))
			return (1);
		if ((e = e + d) >= 0.5)
		{
			i[1] = i[1] + 1;
			e -= 1.0;
		}
		i[0]++;
	}
	while (i[0] > i[2])
	{
		if (fill_pixel(env, i[0], i[1]))
			return (1);
		e = e - d;
		e <= 0.5 ? i[1] = i[1] - 1 : 0;
		e <= 0.5 ? e += 1.0 : 0;
		i[0]--;
	}
	return (0);
}

static int	algo_bresenham_y(double i[4], t_env *env, double e, double d)
{
	while (i[1] < i[3])
	{
		if (fill_pixel(env, i[0], i[1]))
			return (1);
		if ((e = e + d) >= 0.5)
		{
			i[0] = i[0] + 1;
			e -= 1.0;
		}
		i[1]++;
	}
	while (i[1] > i[3])
	{
		if (fill_pixel(env, i[0], i[1]))
			return (1);
		e = e - d;
		e <= 0.5 ? i[0] = i[0] - 1 : 0;
		e <= 0.5 ? e += 1.0 : 0;
		i[1]--;
	}
	return (0);
}

static int	algo_bresenham_yn(double i[4], t_env *env, double e, double d)
{
	while (i[1] < i[3])
	{
		if (fill_pixel(env, i[0], i[1]))
			return (1);
		if ((e = e + d) <= 0.5)
		{
			i[0] = i[0] - 1;
			e += 1.0;
		}
		i[1]++;
	}
	while (i[1] > i[3])
	{
		if (fill_pixel(env, i[0], i[1]))
			return (1);
		e = e - d;
		e >= 0.5 ? i[0] = i[0] + 1 : 0;
		e >= 0.5 ? e -= 1.0 : 0;
		i[1]--;
	}
	return (0);
}

static int	algo_bresenham_xn(double i[4], t_env *env, double e, double d)
{
	while (i[0] < i[2])
	{
		if (fill_pixel(env, i[0], i[1]))
			return (1);
		if (!(e = e - d))
		{
			i[1] = i[1] - 1;
			e -= 1.0;
		}
		i[0]++;
	}
	while (i[0] > i[2])
	{
		if (fill_pixel(env, i[0], i[1]))
			return (1);
		e = e - d;
		e >= 0.5 ? i[1] = i[1] + 1 : 0;
		e >= 0.5 ? e -= 1.0 : 0;
		i[0]--;
	}
	return (0);
}

/*
** algo_bresenham:
**	allow the possibility to draw line in image
*/

int			algo_bresenham(double index[4], t_env *env)
{
	double	dx;
	double	dy;

	dy = index[3] - index[1];
	dx = index[2] - index[0];
	if (dx / dy > 1)
		return (algo_bresenham_x(index, env, 0, dy / dx));
	else if (dx / dy <= 1 && dx / dy > 0)
		return (algo_bresenham_y(index, env, 0, dx / dy));
	else if (dx / dy <= 0 && dx / dy >= -1)
		return (algo_bresenham_yn(index, env, 0, dx / dy));
	else
		return (algo_bresenham_xn(index, env, 0, dy / dx));
	return (0);
}
