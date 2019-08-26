/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/31 15:52:28 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/10 17:57:03 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

/*
** reset:
**	small function to reset default params
*/

static void	reset(t_env *env)
{
	env->marge = 4;
	env->zoom = 50;
	env->speedo = 3;
	env->help = false;
	env->highlight_path = false;
	env->x_img = WIN_SIZE_X / 4;
	env->y_img = WIN_SIZE_Y / 4;
}

/*
** keyboard_events2:
**	the last part of a function call after a keyboard event
*/

int			keyboard_events2(int key, void *data)
{
	t_env *env;

	env = (t_env*)data;
	if (key == H)
		env->help = (env->help) ? true : false;
	else if (key == R)
		reset(env);
	else if (key == L)
		env->highlight_path = (env->highlight_path) ? true : false;
	return (0);
}

/*
** keyboard_events:
**	the first part of a function call after a keyboard event
*/

int			keyboard_events(int key, void *data)
{
	t_env *env;

	env = (t_env*)data;
	if (key == ESC)
		exit(0);
	if (key == PUP && env->speedo < 20)
		env->speedo += 1;
	else if (key == PDOWN && env->speedo > 0)
		env->speedo -= 1;
	else if (key == LESS && env->marge > 0)
		env->marge -= 3;
	else if (key == PLUS && env->marge < 10)
		env->marge += 3;
	else if (key == DOWN || key == S)
		env->x_img += env->speedo;
	else if (key == UP || key == W)
		env->x_img -= env->speedo;
	else if (key == LEFT || key == A)
		env->y_img -= env->speedo;
	else if (key == RIGHT || key == D)
		env->y_img += env->speedo;
	keyboard_events2(key, data);
	put_img(env, *(env->data));
	return (0);
}

/*
** keyboard_events:
**	this is the fuction call after a mouse event
*/

int			mouse_events(int button, int x, int y, void *data)
{
	t_env *env;

	env = (t_env*)data;
	if (button == ZOOM_IN && env->zoom < 100)
	{
		env->zoom += 1;
		put_img(env, *(env->data));
	}
	else if (button == ZOOM_OUT && env->zoom > 1)
	{
		env->zoom -= 1;
		put_img(env, *(env->data));
	}
	return (0);
}
