/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_anthill_tube.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 15:37:59 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 15:55:37 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	check_and_get_tube(t_room *begin, t_tube *tube, char *s1, char *s2)
{
	char	scan;

	scan = 3;
	if (!ft_strcmp(s1, s2))
	{
		free(s1);
		free(s2);
		return (false);
	}
	while (begin && scan)
	{
		if (scan & 2 && !ft_strcmp(begin->name, s1))
		{
			tube->salle1 = begin->salle_id;
			scan = scan & 1;
		}
		else if (scan & 1 && !ft_strcmp(begin->name, s2))
		{
			tube->salle2 = begin->salle_id;
			scan = scan & 2;
		}
		begin = begin->next;
	}
	free(s1);
	free(s2);
	if (scan != 0)
		return (false);
	return (true);
}

static t_bool	split_line_for_tube(const char *s, char **name_room_1, char **name_room_2)
{
	UINT i;

	i = 0;
	if (!s[i])
		return (false);
	while (s[i] != '-')
		i++;
	if (i == 0)
		return (false);
	if (!(*name_room_1 = ft_strsub(s, 0, i)))
		return (false);
	if (!(*name_room_2 = ft_strsub(s, i + 1, ft_strlen(&s[i + 1]))))
	{
		free(*name_room_1);
		return (false);
	}
	return (true);
}

t_bool			manage_tube(const char *s, char *se, t_tube **tube, t_room *room)
{
	t_tube	*tmp_tube;
	char	*name_room1;
	char	*name_room2;

	*se = *se & 16 ? *se & 15 : *se;
	if (*se != 15)
		return (false);
	if (!(tmp_tube = new_tube(0, 0)))
		return (false);
	if (split_line_for_tube(s, &name_room1, &name_room2))
	{
		free(tmp_tube);
		return (false);
	}
	if (check_and_get_tube(room, tmp_tube, name_room1, name_room2))
	{
		free(tmp_tube);
		return (false);
	}
	(*tube)->next = tmp_tube;
	*tube = (*tube)->next;
	return (true);
}
