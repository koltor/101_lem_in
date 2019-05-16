/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:38:20 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 18:25:41 by matheme     ###    #+. /#+    ###.fr     */
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
	struct s_room	*next;
}					t_room;

typedef	struct		s_tube
{
	UINT			salle1;
	UINT			salle2;
	struct s_tube	*next;
}					t_tube;


typedef enum e_bool t_bool;

/*
** fonction for the parsing
*/
char			*get_clean_line(int fd, char option);
t_bool			check_and_parse_anthill(const int file_fd, t_room **room, t_tube **tube);
t_bool			manage_room(const char *s, char *se, t_room **room, t_room *begin);
t_room			*new_room(int x, int y, char *name, char salle_id);
void			free_room(t_room *room);
t_tube			*new_tube(UINT id_salle1, UINT id_salle2);
void			free_tube(t_tube *tube);

/*
** error
*/

void			error(void);
void			usage(void);

/*
** debug
*/

void			show_room(t_room *room);
#endif