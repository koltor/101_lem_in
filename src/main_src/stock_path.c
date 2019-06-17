/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stock_path.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/12 16:51:37 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/17 10:23:21 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_path_list(t_list **begin, t_tube tube)
{
	t_path  new;
	t_list *new_elem;
	int i;

	i = 0;
	if (!(new.rooms_to_go = (UINT *)malloc(sizeof(UINT) * (tube.turn))))	{
		f_error(ERR_MALLOC, NULL);
		return ;
	}
	new.path_id = tube.path_id;
	new.turn = tube.turn;
	new_elem = ft_lstnew(&new, sizeof(new));
	ft_lstadd(begin, new_elem);
}

static UINT	browse_list(t_list *begin, t_tube tube)
{
	while (begin)
	{
		if (((t_path*)(begin->content))->path_id == tube.path_id)
			return (1);
		begin = begin->next;
	}
	return (0);
}

static UINT	dead_end(t_data *data, t_room end)
{
	int i;

	i = 0;
	while (i < end.nb_link_tubes)
	{
		if (data->t_tab[end.link_tubes[i]].path_id != 0)
			return (0);
		i++;
	}
	return (1);
}

static UINT	get_longest_path(t_data *data, t_list *begin)
{
	UINT i;
	UINT size_path;
	UINT path_id;

	i = 0;
	size_path = data->t_tab[data->r_tab[1].link_tubes[i]].turn;
	path_id  = data->t_tab[data->r_tab[1].link_tubes[i]].path_id;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		if (size_path >= data->t_tab[data->r_tab[1].link_tubes[i]].turn && browse_list(begin, data->t_tab[data->r_tab[1].link_tubes[i]]) == 0)
		{
			size_path = data->t_tab[data->r_tab[1].link_tubes[i]].turn;
			path_id  = data->t_tab[data->r_tab[1].link_tubes[i]].path_id;
		}
		i++;
	}
	return (path_id);
}

t_list	*get_id_path_list(t_room end, t_data *data)
{
	int	i;
	int	test;
	t_list	*begin;

	i = 0;
	test = 0;
	begin = NULL;
	if (dead_end(data, end) == 1)
	{
		dprintf(1, "aucun chemin n'est arrive a end, on arrete tout\n");
		exit(EXIT_FAILURE);
	}
	while (i < end.nb_link_tubes)
	{
		if (browse_list(begin, data->t_tab[end.link_tubes[i]]) == 0 && data->t_tab[end.link_tubes[i]].path_id == get_longest_path(data, begin))
		{
			set_path_list(&begin, data->t_tab[end.link_tubes[i]]);
			i = 0;
			continue ;
		}
		i++;
	}
	return (begin);
}
