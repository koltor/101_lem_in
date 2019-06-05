/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:38:20 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/05 18:10:14 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
*************************************
***************INCLUDES**************
*************************************
*/

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>

# define UINT unsigned int

/*
** help for option's comprehention
*/

# define O_D (option & 1)
# define O_V (option & 2)
# define O_I (option & 4)
# define LIST_OPTION "vid"

enum	e_bool
{
	true = 0,
	false = 1
};

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	UINT			nb_link_tubes;
	UINT			*link_tubes;
}					t_room;

typedef	struct		s_tube
{
	UINT			salle1;
	UINT			salle2;
	UINT			path_id;
	UINT			turn;
}					t_tube;

typedef	struct		s_turn
{
	UINT			id_room;
	UINT			id_path;
	UINT			turn;
}					t_turn;

typedef struct		s_data
{
	UINT			ants;
	UINT			rooms;
	UINT			tubes;
	struct s_tube	*t_tab;
	struct s_room	*r_tab;
}					t_data;

typedef enum e_bool	t_bool;

/*
**************************************************
**********************PARSING*********************
**************************************************
*/

char				**get_option(int ac, char **av, int *option);
char				*parsing_into_line(const char *path);
char				*scan_line_line(char *s);

t_room				*create_room(UINT size);
t_tube				*create_tube(UINT size);
void				free_room(t_room *r_tab, UINT size);

UINT				get_number_of_room(const char *s);
UINT				get_number_of_tube(const char *s);
UINT				get_number_of_ants(const char *s);

t_bool				stock_anthill(char *file_line, t_data *data);
char				*get_room(char *file_line, t_data *data);
void				get_tube(char *file_line, t_data *data, char *line);

int					is_room(const char *s);
int					is_tube(const char *s);
int					is_order(const char *s);

t_bool				skip_ants_number(char *s);
char				*skip_room(char *s);

/*
**************************************************
***********************PART 1*********************
**************************************************
*/

t_bool				get_nodes(t_data *data);

/*
**************************************************
***********************PART 2*********************
**************************************************
*/

t_bool				browse_map(t_data *data);
void				recursive_bs_turn(t_data *d, t_turn *t, UINT nb, UINT lap);
UINT				get_id_room(t_tube tubes, UINT id_room);

UINT				destroy_turn(t_turn *turns, UINT o, UINT id, UINT c);
void				destroy_path(t_tube *tubes, t_room room, UINT id);

/*
**************************************************
***********************ERROR**********************
**************************************************
*/

# define ERR_MALLOC 			1  // malloc a planté
# define ERR_OPEN				2  //impossible d'ouvrir
# define ERR_READ				3  //impossible de lire
# define ERR_OCCURD				4  //une erreur est survenu
# define ERR_DUPLICATE_STR		5 //
# define ERR_DUPLICATE_END		6 //
# define ERR_TUBES_FORMAT		7  // erreur format de tube
# define ERR_TUBES				8  // au moins 1 chemin
# define ERR_ROOMS				9  // au moins 2 salles
# define ERR_ANTS				10 // le nombre de ants ne peut pas etre negatif
# define ERR_ANTS_SPACE			11 // espace present autour du nombre de fourmis
# define ERR_LACK_BEGIN			12 // pas de debut dans la fourmiliere
# define ERR_LACK_END			13 // pas de fin dans la fourmiliere
# define ERR_ROOM_FORMAT		14 // erreur format de room
# define ERR_DUPL_ROOM			15 // 2 salles ont le meme nom
# define ERR_DUPL_XY_ROOM		16 // 2 salles ont les meme coordonnées
# define ERR_DUPL_TUBE			17 // Attention: 2 chemins sont identiques
# define ERR_LINK_TUBE_ITSELF	18 // Attention: 2 chemins sont identiques
# define ERR_EMPTY_FILE			19 // fichier vide
# define ERR_ORDER				20 // ordre invalide
# define ERR_OVERFLOW			21 // overflow sur les salles
# define ERR_ONLY_COMMENT		22 // que des commentaires

void				usage(void);
void				usage_option(char c);
void				*f_error(char value, void *data);
void				str_error(int error);

/*
***************************************************
*************debug*********************************
***************************************************
*/

void				debug_lem_in(t_data *data);
void				debug_main(int option);
void				global_info(t_data *data);
void				show_turns(t_turn *turns, UINT size);

/*
***************************************************
**********************lib_plus*********************
***************************************************
*/

size_t				ft_strlenc(const char *s, char c);
char				*ft_strsub_c(const char *src, char c);
char				*ft_revstrsub_c(const char *src, char c);
long				atol_id(const char *s, char c, UINT index);

/*
**************************************************
*******************VISUALISATEUR******************
**************************************************
*/

void				main_visualisateur(t_data data);
#endif
