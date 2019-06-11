#include "lem_in.h"
/*

   char	*get_name_room(t_room room, t_data *data, t_tube tube)
   {
   if (ft_strcmp(data->r_tab[tube.salle1].name,  room.name) == 0)
   return (data->r_tab[tube.salle2].name);
   return (data->r_tab[tube.salle1].name);
   }

   UINT get_id_room(char *str, t_data *data)
   {
   UINT i;

   i = 0;
   while (i < data->rooms)
   {
   if (ft_strcmp(str, data->r_tab[i].name) == 0)
   return (i);
   i++;
   }
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

UINT	get_tab_size(char **tab)
{
	UINT ret;

	ret = 0;
	while (tab[ret])
		ret++;
	return (ret);
}


void	fill_link_with_rooms(t_list *elem, t_room r_path, t_data *data)
{
	UINT i;
	UINT id_room;

	i = 0;
	id_room = 1;
	while (id_room != 0)
	{
		while (i < room.nb_link_tubes)
		{
			if (((t_path*)(elem->content))->path_id == data->t_tab[room.link_tubes[i]].path_id)
			{
				ft_strdel(&(((t_path*)(elem->content))->rooms_to_go[data->t_tab[data->r_tab[id_room].link_tubes[i]].turn - 1]));
				((t_path*)(elem->content))->rooms_to_go[data->r_tab[id_room].link_tubes[i].turn - 1] = get_name_next_room(r_path);
				break ;
			}
			i++;
		}
		id_room = get_id_room(data->t_tab[data->r_tab[id_room].link_tubes[i]].turn - 1, data->r_tab[id_room].link_tubes[i]);
	}
	ft_strdel(&(((t_path*)(elem->content))->rooms_to_go[0]));
	((t_path*)(elem->content))->rooms_to_go[0] = ft_strdup(data->r_tab[0].name);
}

void	stock_rooms_to_go(t_list *begin, t_data *data) // id end path va nous servir si on veut partir de end et 
	// aller a start ou si on veut partir de start et aller a end
{
	UINT id_curr_room;

	id_curr_room = 1;
	while (begin)
	{
		fill_link_with_rooms(*begin, data->r_tab[id_curr_room], data);
		begin = begin->next;
	}
}
