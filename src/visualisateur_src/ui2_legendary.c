/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ui2_legengary.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/05 17:37:16 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/05 17:39:36 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

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
