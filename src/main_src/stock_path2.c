#include "lem_in.h"

UINT	get_tab_size(char **tab)
{
	UINT ret;

	ret = 0;
	while (tab[ret])
		ret++;
	return (ret);
}

char	*get_name_room(t_room room, t_data *data, t_tube tube)
{
	if (ft_strcmp(data->r_tab[tube.salle1].name,  room.name) == 0)
		return (data->r_tab[tube.salle2].name);
	return (data->r_tab[tube.salle1].name);
}

UINT	browse_tubes(t_list *elem, t_room room, t_data *data)
{
	int i;
	UINT j;
	UINT id_next_room;

	i = 0;
	id_next_room = 0;
	j = get_tab_size(((t_path*)(elem->content))->rooms_to_go) - 1;
	dprintf(1, "tab size = %d\n", j);
	while (i < room.nb_link_tubes)
	{
		if (((t_path*)(elem->content))->path_id == data->t_tab[room.link_tubes[i]].path_id)
		{
			dprintf(1, "hey qu y a t il dans cette case %s\n", ((t_path*)(elem->content))->rooms_to_go[j]);
			ft_strdel(&(((t_path*)(elem->content))->rooms_to_go[j]));	
			((t_path*)(elem->content))->rooms_to_go[j] = ft_strdup(get_name_room(room, data, data->t_tab[room.link_tubes[i]]));
			return ();
		}
		i++;
	}
}

void	stock_rooms_to_go(t_list **begin, t_data *data)
{
	UINT id_curr_room;

	id_curr_room = 1;
	while (*begin)
	{
		while (id_curr_room != 0)
			id_curr_room = browse_tubes(*begin, data->r_tab[id_curr_room], data);
		begin = begin->next;
	}
}
