/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_get_tube.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:48:04 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/27 15:59:52 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void		check_duplicate_tube(t_tube *t_tab, UINT size)
{
	UINT	i;
	UINT	j;
	t_tube	tube;

	i = 0;
	while (i < size)
	{
		tube = t_tab[i];
		j = i + 1;
		while (j < size)
		{
			if ((tube.salle1 == t_tab[j].salle1 &&
				tube.salle2 == t_tab[j].salle2) ||
				(tube.salle1 == t_tab[j].salle2 &&
				tube.salle2 == t_tab[j].salle1))
			{
				f_error(ERR_DUPL_TUBE, NULL);
				return ;
			}
			j += 1;
		}
		i += 1;
	}
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

static t_bool	check_room_exist(const char *n, t_room *r_tab, t_data *data, UINT *r)
{
	char	d;
	UINT	s;
	UINT	e;

	d = n[1];
	s = data->abc.abc_start[n[0]] - 1;
	e = s + data->abc.abc_len[n[0]] + 1;
	while (++s < e)
	{
		if (d != r_tab[s].name[1])
			continue ;
		if (!ft_strcmp(n, r_tab[s].name))
		{
			*r = s;
			return (true);
		}
	}
	if (!ft_strcmp(n, r_tab[0].name))
	{
		*r = 0;
		return (true);
	}
		if (!ft_strcmp(n, r_tab[1].name))
	{
		*r = 1;
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
	if ((check_room_exist(s1, data->r_tab, data, &(tube->salle1))))
		return (exit_slft(ERR_ROOM_NOT_DEFINE, false, s1, s2));
	if ((check_room_exist(s2, data->r_tab, data, &(tube->salle2))))
		return (exit_slft(ERR_ROOM_NOT_DEFINE, false, s1, s2));
	if (tube->salle1 == tube->salle2)
		return (exit_slft(ERR_LINK_TUBE_ITSELF, false, s1, s2));
	data->r_tab[tube->salle2].nb_link_tubes += 1;
	data->r_tab[tube->salle1].nb_link_tubes += 1;
	return (exit_slft(-1, true, s1, s2));
}

/*
** get_tube:
**	transform the last part of the file into tube_data
**	parameters
**		the file_line of the file
**		the struct data
**		the previous line how the function get_room stop
**	variable
**	just an id to move on the tube_table
**	return value
**		affect an error if an error occurd
*/

void			get_tube(char *file_line, t_data *data, char *line)
{
	UINT	id;
	int		ret;

	id = 1;
	if (!is_tube(line))
	{
		if (split_line_for_tube(line, data, &(data->t_tab[0])))
		{
			data->tubes = 0;
			return ;
		}
	}
	while ((line = scan_line_line(file_line)))
	{
		if ((ret = is_tube(line)) == 1)
			continue ;
		if (ret == -1 || split_line_for_tube(line, data, &(data->t_tab[id])))
			break ;
		id += 1;
	}
	if (ret == -1)
		f_error(ERR_TUBES_FORMAT, NULL);
	data->tubes = id;
	//check_duplicate_tube(data->t_tab, data->tubes);
}
