/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ui2_legendary.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/05 17:37:16 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/10 17:38:22 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

/*
** legendary:
** enabled the display of the legends
**	parameters
**		need the struct env
*/

void	legendary(t_env env)
{
	void *mlx;
	void *win;

	mlx = env.mlx_ptr;
	win = env.win_ptr;
	mlx_string_put(mlx, win, 5, WIN_SIZE_Y - 20, 0x00ff00, "GREEN:");
	mlx_string_put(mlx, win, 75, WIN_SIZE_Y - 20, 0xaaaaaa, "start anthill");
	mlx_string_put(mlx, win, 345, WIN_SIZE_Y - 20, 0xff0000, "RED:");
	mlx_string_put(mlx, win, 390, WIN_SIZE_Y - 20, 0xaaaaaa, "end anthill");
	mlx_string_put(mlx, win, 630, WIN_SIZE_Y - 20, 0xffffff, "WHITE:");
	mlx_string_put(mlx, win, 700, WIN_SIZE_Y - 20, 0xaaaaaa, "room");
	mlx_string_put(mlx, win, 790, WIN_SIZE_Y - 20, 0x5E450E, "BROWN:");
	mlx_string_put(mlx, win, 870, WIN_SIZE_Y - 20, 0xaaaaaa, "links");
}

/*
** other_infomations:
** enabled the display of additionnal information
**	parameters
**		need the struct env
*/

void	other_infomations(t_env env)
{
	void	*mlx;
	void	*win;
	int		clr;

	mlx = env.mlx_ptr;
	win = env.win_ptr;
	clr = 0xaaaaaa;
	mlx_string_put(mlx, win, 5, 85, clr, "======================");
	mlx_string_put(mlx, win, 5, 105, clr, "colonne envoyes:");
	mlx_string_put(mlx, win, 5, 125, clr, "chemin trouves:");
	mlx_string_put(mlx, win, 5, 145, clr, "numéro de tour:");
}
