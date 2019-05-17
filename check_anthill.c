/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_anthill.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:42:35 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 16:38:09 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	return_of_checker(t_bool value, char **line)
{
	if (*line)
		free(*line);
	return (value);
}

static void		return_on_begin(t_room **rbegin, t_room **room, t_tube **tbegin, t_tube **tube)
{
		*tube = (*tbegin)->next;
		free(*tbegin);
		*room = (*rbegin)->next;
		free(*rbegin);
}

/*
** check_anthill:
**	parameters
**		need the path of the file you want to check
**	variables
**		FILE_FD contains value of the fd_file after open
**		SE it's a binary checker of information
**		*	16								8		4		2		1
**		*	end of enumaration of rooms		end++	start++	##end	#start
**		LINE is a tempory memory containing a line of the file
**	return value
**		TRUE if the anthill_file is CORRECT
**		FALSE if the anthill_file is WRONG
*/

t_bool			check_and_parse_anthill(const int file_fd, t_room **room, t_tube **tube, UINT *nb_fourmis)
{
	char			se;
	int				nb_fourmis_int;
	char			*line;
	t_room			*begin_room;
	t_tube			*begin_tube;

	se = 16;
	begin_room = *room;
	begin_tube = *tube;
	if ((line = get_clean_line(file_fd, 1)))
	{
		nb_fourmis_int = atoi(line);
		if (nb_fourmis_int <= 0)
		{
			free(line);
			return (false);
		}
		*nb_fourmis = (UINT)nb_fourmis_int;
		free(line);
	}
	while ((line = get_clean_line(file_fd, 1)))
	{
		if (line[0] == '#')
		{
			if (manage_diese(line, &se))
			{
				return_on_begin(&begin_room, room, &begin_tube, tube);
				return (return_of_checker(false, &line));
			}
		}
		else if (!ft_strchr(line, ' '))
		{
			if (manage_tube(line, &se, tube, begin_room->next))
			{
				return_on_begin(&begin_room, room, &begin_tube, tube);
				return (return_of_checker(false, &line));
			}
		}
		else
		{
			if (manage_room(line, &se, room, begin_room->next))
			{
				return_on_begin(&begin_room, room, &begin_tube, tube);
				return (return_of_checker(false, &line));
			}
		}
		free(line);
	}
	return_on_begin(&begin_room, room, &begin_tube, tube);
	return (return_of_checker(true, &line));
}
