/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_anthill_room.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 18:16:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 18:22:06 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	split_line_for_room(const char *s, int *x, int *y, char **name)
{
	unsigned int i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (!s[i])
		return (false);
	if(!(*name = ft_strsub(s, 0, i)))
		return (false);
	if (!s[i])
	{
		free(*name);
		return (false);
	}
	i++;
	*x = ft_atoi(&s[i]);
	while (s[i] && s[i] != ' ')
		i++;
	if (!s[i])
	{
		free(*name);
		return (false);
	}
	*y = ft_atoi(&s[i]);
	return (true);
}

static t_bool	check_binome_room(t_room *room, t_room *begin)
{
	while (begin)
	{
		if (!ft_strcmp(room->name, begin->name))
			return (false);
		if (room->x == begin->x && room->y == begin->y)
			return (false);
		begin = begin->next;
	}
	return (true);
}

static t_room  *select_good_room(char *se)
{
    t_room		*tmp;
    
    if (!(*se & 16))
		return (NULL);
	if ((*se & 1) && !(*se & 4) && (*se = *se | 4))
		tmp = new_room(0, 0, NULL, 1);
	else if ((*se & 2) && !(*se & 8) && (*se = *se | 8))
		tmp = new_room(0, 0, NULL, 2);
	else
		tmp = new_room(0, 0, NULL, 0);
    return (tmp);
}

/*
** manage_room:
**	parameters
		need a string containing the information
		THE binary checker SE
		and the chain_list_of_room for the stockage
	variables
		just a pointor for create the new room
	return value
		0 if all it's OK
		1 if an error is detect
**
*/


t_bool	manage_room(const char *s, char *se, t_room **room, t_room *begin)
{
	t_room		*tmp;
	static UINT salle_id = 2;

    if (!(tmp = select_good_room(se)))
        return (false);
	if(split_line_for_room(s, &tmp->x, &tmp->y, &tmp->name))
	{
		free (tmp);
		return (false);
	}
	if (check_binome_room(tmp, begin))
	{
		free (tmp->name);
		free (tmp);
		return (false);
	}
	if (!tmp->salle_id)
	{
		salle_id += 1;
		tmp->salle_id = salle_id;
	}
	(*room)->next = tmp;
	*room = (*room)->next;
	return (true);
}