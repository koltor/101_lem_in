/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_get_tube.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 17:01:11 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 15:44:30 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

/*
** check_room_exist:
**	parameters
**		a name of a room
**		the room_tab
**		the size of the room_tab
**	return value
**		the id of the room if the room exist
**		-1 otherwise
*/

static t_bool	check_room_exist(const char *n, t_room *r_tab, UINT size, UINT *r)
{
	while (--size)
	{
		if (!ft_strcmp(n, r_tab[size].name))
		{
			*r = size; 
			return (true);
		}
	}
	if (!ft_strcmp(n, r_tab[size].name))
	{
		*r = size; 
		return (true);
	}
	return (false);
}

/*
** check_room_exist:
**	parameters
**		a name of a room
**		the room_tab
**		the size of the room_tab
**	return value
**		the id of the room if the room exist
**		-1 otherwise
*/

static t_bool	exit_slft(UINT err, t_bool value, char *s1, char *s2)
{
	f_error(err, NULL);
	s1 ? free(s1) : 0;
	s2 ? free(s2) : 0;
	return (value);
}

/*
** exit_slft:
**	quit properly the function split_line_for_tube
**	parameters
**		value to free
**		the value of the f_error
**		return value
**	return value
**		true of the data is collect
**		false otherwise
*/

static t_bool	split_line_for_tube(char *line, t_data *data, t_tube *tube)
{
	char	*s1;
	char	*s2;

	if (!(s1 = ft_strsub_c(line, '-')))
		return (exit_slft(ERR_MALLOC, false, NULL, NULL));
	if (!(s2 = ft_revstrsub_c(line, '-')))
		return (exit_slft(ERR_MALLOC, false, s1, NULL));
	 if ((check_room_exist(s1, data->r_tab, data->rooms, &(tube->salle1))))
		return (exit_slft(ERR_ROOM_NOT_DEFINE, false, s1, s2));
	if ((check_room_exist(s2, data->r_tab, data->rooms, &(tube->salle2))))
		return (exit_slft(ERR_ROOM_NOT_DEFINE, false, s1, s2));
	if (tube->salle1 == tube->salle2)
		return (exit_slft(ERR_LINK_TUBE_ITSELF, false, s1, s2));
 	data->r_tab[tube->salle2].nb_link_tubes += 1;
	data->r_tab[tube->salle1].nb_link_tubes += 1;
	return (exit_slft(-1, true, s1, s2));
}

void	get_tube_thread_main(char *file_line, t_data *data, t_thread tube, char *line)
{
	UINT	id;
	int		ret;
    UINT	stop;

	id = (tube.id - 1) * tube.section;
	stop = tube.section;
	if (!is_tube(line))
	{
		if (split_line_for_tube(line, data, &(data->t_tab[id])))
		{
			if (id < tube.thread->tubes)
				tube.thread->tubes = id;
			return ;
		}
		id++;
		stop--;
	}
	while (stop)
	{
		if (!(line = scan_line_line_for_threading(file_line, tube.id - 1)))
			break ;
		if ((ret = is_tube(line)) == 1)
			continue ;
		if (ret == -1 || split_line_for_tube(line, data, &(data->t_tab[id])))
		{
			if (id < tube.thread->tubes)
				tube.thread->tubes = id;
			break ;
		}
			
		stop--;
		id += 1;
	}
	if (ret == -1)
		f_error(ERR_TUBES_FORMAT, NULL);
}