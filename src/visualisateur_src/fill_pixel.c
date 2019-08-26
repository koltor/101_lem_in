/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_pixel.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/05 17:35:18 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 15:40:16 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

/*
** fill_pixel:
**	parameters
**		need the struct env
**		the pos_x of the pixel you want to fill
**		the pos_y of the pixel you want to fill
**	variables
**		int pos for save of the pixel in the string
**	return value
**		1 if the pixel is in the windown
**		0 if the pixel is not in the windown
*/

int				fill_pixel(t_env *env, int x, int y)
{
	int	pos;

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
