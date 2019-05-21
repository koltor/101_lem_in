/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 19:47:54 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_bool	exit_lem_in(t_bool value, char *file_line, t_room *room, t_tube *tube)
{
	if (file_line)
		free(file_line);
	if (room)
		free(room);
	if (tube)
		free(tube);
	return (value);
}

t_bool	split_line_for_room(char *line, t_room *room)
{
	static UINT	id = 2;

	if (!(room->name = ft_strsub_c(line, ' ')))
		return (false);
	room->x = atoi_id(line, ' ', 1);
	room->y = atoi_id(line, ' ', 1);
	room->salle_id = id;
	id++;
	return (true);
}

char	manage_diese(const char *s)
{
	if (s && s[0] != '#')
		return (0);
	if (!strcmp(s, "##start"))
		return (1);
	if (!strcmp(s, "##end"))
		return (2);
	return (0);
}

void	get_room(char *file_line, t_room *room)
{
	char	*line;
	int		i_room;
	int		ret;
	char	spe;

	i_room = 2;
	spe = 0;
	scan_line_line(file_line);
	while ((line = scan_line_line(file_line)))
	{
		if (!spe && (spe = manage_diese(line)))
			continue ;
		if ((ret = is_room(line) == 0))
		{
			spe == 0 ? split_line_for_room(line, &room[i_room]) : 0;
			spe == 1 ? split_line_for_room(line, &room[0]) : 0;
			spe == 2 ? split_line_for_room(line, &room[1]) : 0;
			if (!spe)
				i_room += 1;
			spe = 0;
		}
		else if (ret == -1)
			break ;
	}
}

t_bool	stock_anthill(char *file_line, UINT *ants, t_room *room, t_tube *tube)
{
	(void)tube;
	(void)room;
	if (!(*ants = get_number_of_ants(file_line)))
		return (false);
	get_room(file_line, room);
	return (true);
}

t_bool	lem_in(const char *path)
{
	char	*file_line;
	UINT	ants_number;
	t_room	*room_tab;
	t_tube	*tube_tab;

	if (!(file_line = parsing_into_line(path)))
		return (exit_lem_in(false, NULL, NULL, NULL));
	if (!(room_tab = malloc(sizeof(t_room) * (get_number_of_room(file_line) + 1))))
		return (exit_lem_in(false, file_line, NULL, NULL));
	if (!(tube_tab = malloc(sizeof(t_room) * (get_number_of_tube(file_line) + 1))))
		return (exit_lem_in(false, file_line, room_tab, NULL));
	dprintf(1, "salle: %u\n", get_number_of_room(file_line));
	dprintf(1, "tube: %u\n", get_number_of_tube(file_line));
	stock_anthill(file_line, &ants_number, room_tab, tube_tab);
	dprintf(1, "fourmis: %d\n", ants_number);
	return (exit_lem_in(false, file_line, room_tab, tube_tab));
}

int		main(int ac, char **av)
{
	char d;

	if (ac == 2)
		lem_in(av[1]);
	else
		usage();
	d = *(char*)f_error(0, NULL);
	dprintf(1, "Retour error: %d\n", (int)d);
	return (0);
}
