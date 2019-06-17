/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stock_path2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/12 17:02:06 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/17 09:20:34 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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

	//	printf("id de la liste %u id du tube %u turn = %u\n", ((t_path*)(elem->content))->path_id, data->t_tab[croom.link_tubes[i]].path_id, data->t_tab[croom.link_tubes[i]].turn);
		if (((t_path*)(elem->content))->path_id == data->t_tab[croom.link_tubes[i]].path_id
				&& ((t_path*)(elem->content))->turn == data->t_tab[croom.link_tubes[i]].turn)
		{
			((t_path*)(elem->content))->rooms_to_go[data->t_tab[croom.link_tubes[i]].turn - 1] = get_id_room(data->t_tab[croom.link_tubes[i]], get_room_id(croom.name, data));
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
	UINT turn_cp;

	UINT test = 0;

	i = 0;
	id_room = 1;
	turn_cp = ((t_path*)(elem->content))->turn;
	while (id_room != 0)
	{
		printf("id_room = %d, name room = %s\n", id_room, data->r_tab[id_room].name);
		id_room = fill_link_with_current_room(elem, data->r_tab[id_room], data);
		((t_path*)(elem->content))->turn--;
	}
	((t_path*)(elem->content))->rooms_to_go[0] = 0;
	((t_path*)(elem->content))->turn = turn_cp;
}
/*
void	ft_putint(int *tab)
{
	int i;

	i = 0;
	while (tab[i] != -1)
	{
		printf("id de la room = %u\n", );
		i++;
	}
}
*/

void	print_rooms(t_list *current, t_data *data)
{
	UINT i;

	i = 0;
	while (i < ((t_path *)(current->content))->turn)
	{
		ft_putendl(data->r_tab[((t_path *)(current->content))->rooms_to_go[i]].name);
		i++;
	}
	ft_putendl("--------------------------------");
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
	//	if (fill_link_with_rooms(begin, data->r_tab[1], data) == -1)
	//		destroy_path()
		begin = begin->next;
	}
	while (tmp)
	{
		print_rooms(tmp, data);
		tmp = tmp->next;
	}
}
