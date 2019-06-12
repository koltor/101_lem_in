#include "lem_in.h"
/*

   UINT	get_tab_size(char **tab)
   {
   UINT ret;

   ret = 0;
   while (tab[ret])
   ret++;
   return (ret);
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
   return (get_id_room(((t_path*)(elem->content))->rooms_to_go[j]));
   }
   i++;
   }
   }*/

char	*get_name_room(t_room room, t_data *data, t_tube tube)
{
	if (ft_strcmp(data->r_tab[tube.salle1].name,  room.name) == 0)
		return (data->r_tab[tube.salle2].name);
	return (data->r_tab[tube.salle1].name);
}


UINT	get_room_id(char *str, t_data *data)
{
	UINT i;

	i = 0;
	while (i < data->rooms)
	{
		if (ft_strcmp(str, data->r_tab[i].name) == 0)
			return (i);
		i++;
	}
	printf("get_room_id bug dans la matrice\n");
	return (-1);
}

UINT	fill_link_with_current_room(t_list *elem, t_room croom, t_data *data)
{
	UINT i;

	i = 0;
	while (i < croom.nb_link_tubes)
	{
		if (((t_path*)(elem->content))->path_id == data->t_tab[croom.link_tubes[i]].path_id)
		{
			ft_strdel(&(((t_path*)(elem->content))->rooms_to_go[data->t_tab[croom.link_tubes[i]].turn - 1]));
			((t_path*)(elem->content))->rooms_to_go[data->t_tab[croom.link_tubes[i]].turn - 1] =
			ft_strdup(get_name_room(croom, data, data->t_tab[croom.link_tubes[i]]));
			break ;
		}
		i++;
	}
	return (get_room_id(get_name_room(croom, data, data->t_tab[croom.link_tubes[i]]), data));
}

void	fill_link_with_rooms(t_list *elem, t_room r_path, t_data *data)
{
	UINT i;
	UINT id_room;

	i = 0;
	id_room = 1;
	 while (id_room != 0)
	{
		printf("id_room = %d, name room = %s\n", id_room, data->r_tab[id_room].name);
		id_room = fill_link_with_current_room(elem, data->r_tab[id_room], data);
	}
	ft_strdel(&(((t_path*)(elem->content))->rooms_to_go[0]));
	((t_path*)(elem->content))->rooms_to_go[0] = ft_strdup(data->r_tab[0].name);
}

void	ft_putstr_2d(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_putendl(tab[i]);
		i++;
	}
}

void	stock_rooms_to_go(t_list *begin, t_data *data) // id end path va nous servir si on veut partir de end et 
// aller a start ou si on veut partir de start et aller a end
{
	UINT test = 0;
	t_list *tmp;

	tmp = begin;
	while (begin)
	{
		printf("stock rooms to go num du maillon = %u\n", ++test);
		fill_link_with_rooms(begin, data->r_tab[1], data);
		begin = begin->next;
	}
	while (tmp)
	{
		ft_putstr_2d(((t_path*)(tmp->content))->rooms_to_go);
		tmp = tmp->next;
	}
}
