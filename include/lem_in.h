/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:38:20 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 16:39:11 by matheme     ###    #+. /#+    ###.fr     */
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
# define ULL unsigned long long int
# define ROOM_START 0
# define ROOM_END	1
# define NB_THREAD	8

/*
** help for option's comprehention
*/

# define BUF_SIZE 5
# define USED 0
# define NUSED 1
# define O_D (option & 1)
# define O_V (option & 2)
# define O_I (option & 4)
# define O_M (option & 8)
# define LIST_OPTION "dvim"

enum	e_bool
{
	true = 0,
	false = 1
};

typedef struct		s_room
{
	char			*name;
	UINT			len_name;
	int				x;
	int				y;
	UINT			nb_link_tubes;
	UINT			*link_tubes;
	enum e_bool		used;
}					t_room;

typedef	struct		s_tube
{
	UINT			salle1;
	UINT			salle2;
	ULL				path_id;
	UINT			turn;
	UINT			*tmp_turn;
	enum e_bool		used;
}					t_tube;

typedef	struct		s_turn
{
	UINT			id_room;
	UINT			id_path;
	UINT			turn;
}					t_turn;

typedef struct		s_abc
{
	UINT      		abc_len[128];
	UINT      		abc_start[128];
	UINT			abc_id[128];
}					t_abc;

typedef struct		s_output
{
	char			**out;
	UINT			lap;
	UINT			ants;
	UINT			room_id;
}					t_opt;

typedef struct		s_data
{
	UINT			ants;
	UINT			rooms;
	UINT			tubes;
	UINT			**paths;
	UINT			**ret;
	UINT			path_nbr;
	UINT			lap;
	UINT			len_opt;
	char			*bopt;
	char			*opt;
	struct s_tube	*t_tab;
	struct s_room	*r_tab;
	struct s_abc	abc;
}					t_data;

typedef enum e_bool	t_bool;

/*
**************************************************
**********************PARSING*********************
**************************************************
*/

/* a enlever apres */

#include "ft_printf.h"

/******************/

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
t_bool				get_tube(char *file_line, t_data *data, char *line);
t_bool				get_nodes(t_data *data);

void				check_duplicate_tube(t_tube *t_tab, UINT size);
t_bool				check_dup_room_se(UINT id, t_room *r_tab, UINT st, UINT s);
t_bool				check_dup_room_g(t_room room, t_room *r_tab, UINT st, UINT size);

int					is_room(const char *s);
int					is_tube(const char *s);
int					is_order(const char *s);

t_bool				skip_ants_number(char *s);
char				*skip_room(char *s);

/*parsing for multithreading*/
t_bool				stock_anthill_for_threading(char *file_line, t_data *data);

/*parsing with alphabet_trie*/
void				get_abc_for_room(const char *s, UINT (*abc)[]);
void				get_abc_id_for_room(UINT (*abc_id)[], UINT abc[]);
/*
**************************************************
***********************PART 2*********************
**************************************************
*/

t_bool				browse_map(t_data *data);
void				recursive_bs_turn(t_data *d, t_turn *t, UINT nb, UINT lap);
UINT				get_id_room(t_tube tubes, UINT id_room);
UINT				destroy_turn(t_turn *turns, UINT o, UINT id, UINT c);

/*
**************************************************
***********************PART 3*********************
**************************************************
*/

void				print_potential_paths(t_data *data);
void				fill_path_tab(t_data *data);
void				fill_tabs_with_rooms(t_data *data);
void				print_number_paths(t_data *data);
UINT				count_bits(t_tube tube);
UINT				get_bit_place(ULL path_list);
UINT				find_pname(ULL *path_id, UINT nb_link_tubes_start);
UINT				potential_path_counter(t_data *data);
UINT				max_paths(t_data data);
void				reset_markers(t_data *data);
void				path_sorter2(t_data *data, UINT (*res)[], UINT max_paths);
void				bruteforce_sorter(t_data *data, UINT max_paths, UINT (*res)[]);
void				set_used_rooms(UINT id_tab, t_data *data);
UINT				is_valid(UINT *tab, t_data *data);
UINT				get_compatible_tab_for_pid(UINT pid, t_data *data);
void				get_result_for_path_managment(t_data *data, UINT max_paths);
UINT				get_size_valid_tab(t_data *data, UINT (*res)[], UINT max_paths);
UINT				get_index_valid_tab(t_data *data, UINT (*res)[], UINT max_paths);
UINT				check_path_found(UINT (*curr)[], UINT max_paths, UINT path_nbr);
void				tab_cp(UINT (*curr)[], UINT (*res)[], UINT max_paths);
void				print_tab(UINT (*res)[], UINT max_paths);
void				set_tab_for_bf(UINT (*tab)[], UINT path_nbr, UINT max_paths);
void				set_tab_for_bf(UINT (*res)[], UINT path_nbr, UINT max_paths);

/*
**************************************************
***********************PART 4*********************
**************************************************
*/

void	opti_paths(UINT (*res)[], UINT max_paths, t_data *data);
void	fill_output(t_data *data);
void	stock_file_line(t_data *data, const char *s);

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
# define ERR_LINK_TUBE_ITSELF	18 // Une salle est relier a elle même
# define ERR_EMPTY_FILE			19 // fichier vide
# define ERR_ORDER				20 // ordre invalide
# define ERR_OVERFLOW			21 // overflow sur les salles
# define ERR_ONLY_COMMENT		22 // que des commentaires
# define ERR_ROOM_NOT_DEFINE	23 // salle utilise dans les tubes non defini
# define ERR_ROOM_WRONG_POS		24 //invalide positions sur les salles
# define ERR_NO_ANTS			25 //invalide positions sur les salles

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
long				atol_id(const char *s, char c, UINT index, t_bool *boule);
ULL					bin(char c);
UINT				count_digits(UINT num);

/*
**************************************************
*******************VISUALISATEUR******************
**************************************************
*/

void				main_visualisateur(t_data data);



#endif
