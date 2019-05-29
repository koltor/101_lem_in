/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_get_tube.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:48:04 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 18:35:11 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	check_duplicate_tube(t_tube *t_tab, UINT size)
{
	UINT	i;
	UINT	j;
	t_bool	value;

	i = -1;
	value = false;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (i == j)
				continue ;
			if (t_tab[i].salle1 == t_tab[j].salle1 &&
									t_tab[i].salle2 == t_tab[j].salle2)
				return (*(t_bool*)f_error(ERR_DUPL_TUBE, &value));
			else if (t_tab[i].salle1 == t_tab[j].salle2 &&
						t_tab[i].salle2 == t_tab[j].salle1)
				return (*(t_bool*)f_error(ERR_DUPL_TUBE, &value));
		}
		if (t_tab[i].salle1 == t_tab[i].salle2)
			return (*(t_bool*)f_error(ERR_LINK_TUBE_ITSELF, &value));
	}
	return (true);
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

static long		check_room_exist(const char *name, t_room *r_tab, UINT size)
{
	UINT i;

	i = 0;
	while (i < size)
	{
		if (!ft_strcmp(name, r_tab[i].name))
			return (i);
		i++;
	}
	return (-1);
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

t_bool			exit_slft(UINT err, t_bool value, char *s1, char *s2)
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
	char *s1;
	char *s2;
	long id;

	if (!(s1 = ft_strsub_c(line, '-')))
		return (exit_slft(ERR_MALLOC, false, NULL, NULL));
	if (!(s2 = ft_revstrsub_c(line, '-')))
		return (exit_slft(ERR_MALLOC, false, s1, NULL));
	if (!s1)
		return (exit_slft(-1, false, s2, NULL));
	if (!s2)
		return (exit_slft(-1, false, s1, NULL));
	if ((id = check_room_exist(s1, data->r_tab, data->rooms)) == -1)
		return (exit_slft(-1, false, s1, s2));
	data->r_tab[id].nb_link_tubes += 1;
	tube->salle1 = id;
	if ((id = check_room_exist(s2, data->r_tab, data->rooms)) == -1)
		return (exit_slft(-1, false, s1, s2));
	data->r_tab[id].nb_link_tubes += 1;
	tube->salle2 = id;
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
		if (split_line_for_tube(line, data, &data->t_tab[0]))
		{
			data->tubes = 0;
			return ;
		}
	while ((line = scan_line_line(file_line)))
	{
		if (!(ret = is_tube(line)))
		{
			if (split_line_for_tube(line, data, &data->t_tab[id]))
				break ;
			id += 1;
		}
		else if (ret == -1)
			break ;
	}
	if (ret == -1)
		f_error(ERR_TUBES_FORMAT, NULL);
	data->tubes = id;
	check_duplicate_tube(data->t_tab, data->tubes);
}
