/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_get_tube.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:48:04 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 15:46:56 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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

t_bool			exit_slft(UINT err, t_bool value, char *s1, char *s2)
{
	f_error(err, NULL);
	s1 ? free(s1) : 0;
	s2 ? free(s2) : 0;
	return (value);
}

static t_bool	split_line_for_tube(char *line, t_data *data, t_tube *tube)
{
	char *s1;
	char *s2;
	long id;

	if (!(s1 = ft_strsub_c(line, '-')))
		return (exit_slft(ERR_MALLOC, false, NULL, NULL));
	if (!(s2 = ft_revstrsub_c(line, '-')))
		return (exit_slft(ERR_MALLOC, false, s1, NULL));
	if (!ft_strcmp(s1, s2))
		return (exit_slft(-1, false, s1, s2));
	if ((id = check_room_exist(s1, data->r_tab, data->rooms)) != -1)
		tube->salle1 = id;
	else
		return (exit_slft(-1, false, s1, s2));
	if ((id = check_room_exist(s2, data->r_tab, data->rooms)) != -1)
		tube->salle2 = id;
	else
		return (exit_slft(-1, false, s1, s2));
	return (exit_slft(-1, true, s1, s2));
}

void			get_tube(char *file_line, t_data *data, char *line)
{
	UINT id;

	id = 1;
	if (!is_tube(line))
	{
		if (split_line_for_tube(line, data, &data->t_tab[0]))
		{
			f_error(ERR_LACK_TUBE, NULL);
			return ;
		}
	}
	while ((line = scan_line_line(file_line)))
	{
		if (!is_tube(line))
		{
			if (split_line_for_tube(line, data, &data->t_tab[id]))
				break ;
			id += 1;
		}
	}
	data->tubes = id;
}
