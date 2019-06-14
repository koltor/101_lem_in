/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stock_path.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/12 16:51:37 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/14 14:10:18 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_path_list(t_list **begin, t_tube tube)
{
	t_path  new;
	t_list *new_elem;
	int i;

//	printf("\nallo le turn du tube dans set path_list = %d\n", tube.turn);
	i = 0;
	if (!(new.rooms_to_go = (UINT *)malloc(sizeof(UINT) * (tube.turn)))) // a changer en tableau d int
	{
		f_error(ERR_MALLOC, NULL);
		return ;
	}
	new.path_id = tube.path_id;
	new.turn = tube.turn;
	printf("dans set path list new.turn = %u\n", new.turn);
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
		if (data->t_tab[end.link_tubes[i]].path_id != 0)
			if (browse_list(begin, data->t_tab[end.link_tubes[i]]) == 0)
				set_path_list(&begin, data->t_tab[end.link_tubes[i]]);
		printf("dans init path list elem.turn = %u\n", ((t_path*)(begin->content))->turn);
		i++;
	}
//	print_list_output(begin);
	return (begin);
}
