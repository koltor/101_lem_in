/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visu_lem_in.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/31 11:11:51 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/04 18:30:21 by matheme     ###    #+. /#+    ###.fr     */
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
# define WIN_SIZE_X 700
# define WIN_SIZE_Y 700

/*
** define for keyboard_keys
*/
# define ESC		53
# define PLUS		69
# define LESS		78
# define H			4

/*
** define for mouse button
*/
# define ZOOM_IN	5
# define ZOOM_OUT	4
# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
# define W			13
# define S			1
# define A			0
# define D			2
# define R			15

typedef struct  	s_env
{
	struct s_data	*data;		//pointeur vers la struct data
	
    void        	*mlx_ptr;	//pointeur vers la mlx
    void        	*win_ptr;	//pointeur vers la fenetre
	void			*img_ptr;	//pointeur vers l'image

	char			*img_str;	//str de l'image
	int				bpp;		//besoin pour generer l'image
	int				s_l;		//besoin pour generer l'image
	int				endian;		//besoin pour generer l'image

	double			zoom;  		//permet de zoomer dans ou dezoomer dans la map
	int				marge; 		//permet de mettre une marge minimum entre les salles
	int				x_img; 		//permet de bouger l'image en X
	int				y_img; 		//permet de bouger l'image en Y
	int				color; 		// coulor des salles

	t_bool			help; //permet d'activer ou desactiver les aide de UI
}               	t_env;

int			algo_bresenham(double index[4], t_env *env);
int			fill_pixel(t_env *env, int x, int y);
void		put_img(t_env *env, t_data data);


int			keyboard_events(int key, void *data);
int			mouse_events(int button, int x, int y, void *data);
void		user_interface(t_env env);
#endif
