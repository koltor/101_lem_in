/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ui.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/31 15:55:00 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/10 16:16:28 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

static void	helping_informations_value(t_env env, void *m, void *w)
{
	int		clr;
	char	*zoom;
	char	*depl_x;
	char	*depl_y;
	char	*marge;

	clr = 0xaaaaaa;
	zoom = ft_itoa(env.zoom);
	depl_x = ft_itoa(env.x_img);
	depl_y = ft_itoa(env.y_img);
	marge = ft_itoa(env.marge);
	mlx_string_put(m, w, WIN_SIZE_X - 250, 125, clr, "======================");
	mlx_string_put(m, w, WIN_SIZE_X - 250, 145, clr, "       zoom:");
	mlx_string_put(m, w, WIN_SIZE_X - 100, 145, 0xaa5498, zoom);
	mlx_string_put(m, w, WIN_SIZE_X - 70, 145, clr, "/100");
	mlx_string_put(m, w, WIN_SIZE_X - 250, 165, clr, "deplacement:    x    y");
	mlx_string_put(m, w, WIN_SIZE_X - 130, 165, 0xaa0000, depl_x);
	mlx_string_put(m, w, WIN_SIZE_X - 80, 165, 0x00aa00, depl_y);
	mlx_string_put(m, w, WIN_SIZE_X - 250, 185, clr, " ecartement:");
	mlx_string_put(m, w, WIN_SIZE_X - 120, 185, 0xFF9A09, marge);
	mlx_string_put(m, w, WIN_SIZE_X - 100, 185, clr, " -2/10");
	free(zoom);
	free(depl_x);
	free(depl_y);
}

static void	helping_informations(t_env env)
{
	void	*m;
	void	*w;
	int		clr;
	char	*speed;

	m = env.mlx_ptr;
	w = env.win_ptr;
	clr = 0xaaaaaa;
	speed = ft_itoa(env.speedo);
	mlx_string_put(m, w, WIN_SIZE_X - 250, 25, clr, "       zoom: molette");
	mlx_string_put(m, w, WIN_SIZE_X - 250, 45, clr, "deplacement: hgbd/wasd");
	mlx_string_put(m, w, WIN_SIZE_X - 250, 65, clr, "      marge: + / -");
	mlx_string_put(m, w, WIN_SIZE_X - 250, 85, clr, "   surligne: L ");
	mlx_string_put(m, w, WIN_SIZE_X - 250, 105, clr, "   rapidite: Page ");
	mlx_string_put(m, w, WIN_SIZE_X - 60, 105, 0xffffff, speed);
	if (env.highlight_path)
		mlx_string_put(m, w, WIN_SIZE_X - 100, 85, clr, "(inactif)");
	else
		mlx_string_put(m, w, WIN_SIZE_X - 100, 85, clr, "(actif)");
	free(speed);
}

static void	number_information(t_env env, char *ants, char *rooms, char *tubes)
{
	void	*mlx;
	void	*win;
	int		clr;

	mlx = env.mlx_ptr;
	win = env.win_ptr;
	clr = 0xaaaaaa;
	if (WIN_SIZE_X > 700)
	{
		mlx_string_put(mlx, win, 5, 5, clr, "nombre de fourmis:");
		mlx_string_put(mlx, win, 5, 45, clr, "nombre de liaisons:");
		mlx_string_put(mlx, win, 5, 25, clr, "nombre de salles:");
		mlx_string_put(mlx, win, 210, 5, clr, ants);
		mlx_string_put(mlx, win, 210, 25, clr, rooms);
		mlx_string_put(mlx, win, 210, 45, clr, tubes);
	}
	else
	{
		mlx_string_put(mlx, win, 5, 5, clr, "fourmis:");
		mlx_string_put(mlx, win, 5, 45, clr, "liaisons:");
		mlx_string_put(mlx, win, 5, 25, clr, "salles:");
		mlx_string_put(mlx, win, 110, 5, clr, ants);
		mlx_string_put(mlx, win, 110, 25, clr, rooms);
		mlx_string_put(mlx, win, 110, 45, clr, tubes);
	}
}

static void	first_informations(t_env env, void *m, void *w)
{
	int		clr;
	char	*nb_ants;
	char	*nb_rooms;
	char	*nb_tubes;

	clr = 0xaaaaaa;
	nb_ants = ft_itoa(env.data->ants);
	nb_rooms = ft_itoa(env.data->rooms);
	nb_tubes = ft_itoa(env.data->tubes);
	number_information(env, nb_ants, nb_rooms, nb_tubes);
	free(nb_ants);
	free(nb_rooms);
	free(nb_tubes);
	mlx_string_put(m, w, WIN_SIZE_X - 180, 5, clr, "help: h");
	mlx_string_put(m, w, WIN_SIZE_X / 2 - 70, 5, clr, "quit: esc    reset: r");
	if (env.help)
		mlx_string_put(m, w, WIN_SIZE_X - 100, 5, clr, "(inactif)");
	else
		mlx_string_put(m, w, WIN_SIZE_X - 100, 5, clr, "(actif)");
}

void		user_interface(t_env env)
{
	if (!env.help)
	{
		legendary(env);
		helping_informations(env);
		helping_informations_value(env, env.mlx_ptr, env.win_ptr);
		other_infomations(env);
	}
	first_informations(env, env.mlx_ptr, env.win_ptr);
}
