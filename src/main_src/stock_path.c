#include "lem_in.h"

void	set_path_list(t_list **begin, t_tube tube)
{
	t_path  new;
	t_list *new_elem;

	if (!(new.rooms_to_go = (char **)malloc(sizeof(char *) * tube.turn + 1)))
	{
		f_error(ERR_MALLOC, NULL);
		return ;
	}
	new.rooms_to_go[tube.turn - 1] = NULL;
	new.path_id = tube.path_id;
	new_elem = ft_lstnew(&new, sizeof(new));
	ft_lstadd(begin, new_elem);
}

UINT	browse_list(t_list *begin, t_tube tube)
{
	while (begin)
	{
		if (((t_path*)(begin->content))->path_id == tube.path_id)
			return (1);
		begin = begin->next;
	}
	return (0);
}

UINT	dead_end(t_data *data, t_room end)
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


void	print_list_output(t_list *begin)
{
	int i;

	i = 0;
	while (begin)
	{
		dprintf(1, "maillon numero %d, id_path = %u\n", ++i, ((t_path*)(begin->content))->path_id);
		begin = begin->next;
	}
}

t_list	*get_id_path(t_room end, t_data *data)
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
		i++;
	}
	print_list_output(begin);
	return (begin);
}
