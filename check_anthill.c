/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_anthill.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:42:35 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 18:27:44 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"



t_bool	split_line_for_tube(const char *s, t_room *begin)
{
	unsigned int	i;
	char			scan;
	char 			*name_room_1;
	char			*name_room_2;

	i = 0;
	scan = 3;
	if (!s[i])
		return (false);
	while (s[i] != '-')
		i++;
	if (i == 0)
		return (false);
	if (!(name_room_1 = ft_strsub(s, 0, i)))
		return (false);
	if (!(name_room_2 = ft_strsub(s, i + 1, ft_strlen(&s[i + 1]))))
	{
		free(name_room_1);
		return (false);
	}
	if (!ft_strcmp(name_room_1, name_room_2))
	{
		free(name_room_1);
		free(name_room_2);
		return (false);
	}
	while (begin && scan)
	{
		if (scan & 2 && !ft_strcmp(begin->name, name_room_1))
			scan = scan & 1;
		else if (scan & 1 && !ft_strcmp(begin->name, name_room_2))
			scan = scan & 2;
		begin = begin->next;
	}
	free(name_room_1);
	free(name_room_2);
	if (scan != 0)
		return (false);
	return (true);
}

/*
** manage_diese
**	parameters
*		need a string containing the information
*		THE binary checker SE
**if the ligne of information begin by #
**this function is call ad change the value of SE if the order
**##start or ##end is call
*/

t_bool	manage_diese(const char *s, char *se)
{
	if (!strcmp(s, "##start"))
	{
		if (*se & 1)
			return (false);
		*se = *se | 1;
	}
	else if (!strcmp(s, "##end"))
	{
		if (*se & 2)
			return (false);
		*se = *se | 2;
	}
	return (true);
}

t_bool	manage_tube(const char *s, char *se, t_tube *tube, t_room *room)
{
	*se = *se & 16 ? *se & 15 : *se;
	if (*se != 15)
		return (false);

	if (split_line_for_tube(s, room))
		return (false);
	return (true);
}



static t_bool	return_of_checker(t_room **begin_room, t_room **room, t_bool value, char **line)
{
	if (*line)
		free(*line);
	*room = (*begin_room)->next;
	free(*begin_room);
	return (value);
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

t_bool	check_and_parse_anthill(const int file_fd, t_room **room, t_tube **tube)
{
	char			se;
	char			*line;
	t_room			*begin_room;
	t_tube			*begin_tube;

	se = 16;
	begin_room = *room;
	begin_tube = *tube;
	while((line = get_clean_line(file_fd, 1)))
	{
		if (line[0] == '#')
		{
			if (manage_diese(line, &se))
				return (return_of_checker(&begin_room, room, false, &line));
		}
		else if (!ft_strchr(line, ' '))
		{
			if (manage_tube(line, &se, tube, begin_room->next))
				return (return_of_checker(&begin_room, room, false, &line));
		}
		else
		{
			if (manage_room(line, &se, room, begin_room->next))
				return (return_of_checker(&begin_room, room, false, &line));
		}
		free (line);
	}
	return (return_of_checker(&begin_room, room, true, &line));
}
