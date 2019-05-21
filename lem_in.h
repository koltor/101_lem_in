/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:38:20 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 19:12:32 by matheme     ###    #+. /#+    ###.fr     */
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

#define UINT unsigned int

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
	UINT			salle_id;
}					t_room;

typedef	struct		s_tube
{
	UINT			salle1;
	UINT			salle2;
}					t_tube;


typedef enum e_bool t_bool;

/*************************************************
**********************PARSING*********************
*************************************************/

char	*parsing_into_line(const char *path);
char	*scan_line_line(char *s);

UINT    get_number_of_room(const char *s);
UINT    get_number_of_tube(const char *s);
UINT	get_number_of_ants(const char *s);

char	is_room(const char *s);
char	is_tube(const char *s);

/*************************************************
***********************ERROR**********************
*************************************************/

# define ERR_MALLOC 	1
# define ERR_OPEN		2
# define ERR_READ		3
# define ERR_OCCURD		4
# define ERR_ANTS		10 // le nombre de fourmis ne peut pas etre negatif
# define ERR_ANTS_SPACE	11 // espace present lors de la transmission du nombre de fourmis

void			usage(void);
void			*f_error(char value, void *data);

/**************************************************
*************debug*********************************
**************************************************/


char	detect_char(const char c, char *s);


/**************************************************
**********************lib_plus*********************
***************************************************/

char	*ft_strsub_c(const char *src, char c);
int		atoi_id(const char *s, char c, UINT index);
#endif