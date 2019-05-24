/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:38:20 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 18:21:05 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/************************************
***************INCLUDES**************
*************************************/

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h>

# define UINT unsigned int

/*
** help for option's comprehention
*/

# define D (option & 1)
# define LIST_OPTION "d"

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
}					t_room;

typedef	struct		s_tube
{
	UINT			salle1;
	UINT			salle2;
}					t_tube;

typedef struct		s_data
{
	UINT			ants;
	UINT			rooms;
	UINT			tubes;
	struct s_tube	*t_tab;
	struct s_room	*r_tab;
}					t_data;



typedef enum e_bool t_bool;

/*************************************************
**********************PARSING*********************
*************************************************/

char			**get_option(int ac, char **av, int *option);
char			*parsing_into_line(const char *path);
char			*scan_line_line(char *s);

t_room			*create_room(UINT size);
t_tube			*create_tube(UINT size);
void			free_room(t_room *r_tab, UINT size);

UINT    		get_number_of_room(const char *s);
UINT    		get_number_of_tube(const char *s);
UINT			get_number_of_ants(const char *s);

char			*get_room(char *file_line, t_data *data);
void    		get_tube(char *file_line, t_data *data, char *line);

int				is_room(const char *s);
int				is_tube(const char *s);
int				is_order(const char *s);

void			skip_ants_number(char *s);
char			*skip_room(char *s);

/*************************************************
***********************ERROR**********************
*************************************************/

# define ERR_MALLOC 	1
# define ERR_OPEN		2
# define ERR_READ		3
# define ERR_OCCURD		4
# define ERR_TUBES		8
# define ERR_ROOMS		9
# define ERR_ANTS		10 // le nombre de fourmis ne peut pas etre negatif
# define ERR_ANTS_SPACE	11 // espace present lors de la transmission du nombre de fourmis
# define ERR_LACK_BEGIN	12 // pas de debut dans la fourmiliere
# define ERR_LACK_END	13 // pas de fin dans la fourmiliere
# define ERR_LACK_TUBE	14 // pas de fin dans la fourmiliere

void			usage(void);
void			usage_option(char c);
void			*f_error(char value, void *data);
void			str_error(int error);

/**************************************************
*************debug*********************************
**************************************************/

void			debug_lem_in(t_data *data);
void			debug_main(int option);

/**************************************************
**********************lib_plus*********************
***************************************************/

size_t			ft_strlenc(const char *s, char c);
char			*ft_strsub_c(const char *src, char c);
char			*ft_revstrsub_c(const char *src, char c);
int				atoi_id(const char *s, char c, UINT index);
#endif