/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visu_lem_in.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/31 11:11:51 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 18:41:05 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VISU_LEM_IN_H
# define VISU_LEM_IN_H

# include "lem_in.h"
# include "mlx.h"

/*
** size X and Y of windows
*/
# define WIN_SIZE_X 1700
# define WIN_SIZE_Y 1000

/*
** define for keyboard_keys
*/
# define ESC		53
# define PLUS		69
# define LESS		78
# define H			4
# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
# define W			13
# define S			1
# define A			0
# define D			2
# define R			15
# define L			37
# define PUP		116
# define PDOWN		121

/*
** define for mouse button
*/
# define ZOOM_IN	5
# define ZOOM_OUT	4

typedef struct		s_env
{
	struct s_data	*data;

	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;

	char			*img_str;
	int				bpp;
	int				s_l;
	int				endian;

	double			zoom;
	unsigned char	speedo;
	int				marge;
	int				x_img;
	int				y_img;
	int				color;

	t_bool			highlight_path;
	t_bool			help;
}					t_env;

int					algo_bresenham(double index[4], t_env *env);
int					fill_pixel(t_env *env, int x, int y);
void				put_img(t_env *env, t_data data);
void				show_name_room(t_env *env, t_data data);

int					keyboard_events(int key, void *data);
int					mouse_events(int button, int x, int y, void *data);
void				user_interface(t_env env);
void				legendary(t_env env);
void				other_infomations(t_env env);
#endif
