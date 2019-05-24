/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 18:20:12 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_bool	exit_lem_in_error(char *file_line, t_room *room, t_tube *tube)
{
	if (file_line)
		free(file_line);
	if (room)
		free(room);
	if (tube)
		free(tube);
	return (false);
}

t_bool	exit_lem_in_ok(char *file_line, t_data *data)
{
	free(file_line);
	free(data->t_tab);
	free_room(data->r_tab, data->rooms);
	return (true);
}

t_bool	stock_anthill(char *file_line, t_data *data)
{
	char *line;

	if (!(data->ants = get_number_of_ants(file_line)))
		return (false);
	if (!(line = get_room(file_line, data)))
	{
		data->tubes = 0;
		scan_line_line(NULL);
		return (false);
	}
	get_tube(file_line, data, line);
	scan_line_line(NULL);
	return (true);
}

t_bool	lem_in(const char *path, int option)
{
	char	*file_line;
	t_data	data;

	if (!(file_line = parsing_into_line(path)))
		return (exit_lem_in_error(NULL, NULL, NULL));
	if ((data.rooms = get_number_of_room(file_line)) < 2)
		return (exit_lem_in_error(file_line, NULL, NULL));
	if ((data.tubes = get_number_of_tube(file_line)) < 1)
		return (exit_lem_in_error(file_line, NULL, NULL));
	if (!(data.r_tab = create_room(data.rooms)))
		return (exit_lem_in_error(file_line, NULL, NULL));
	if (!(data.t_tab = create_tube(data.tubes)))
		return (exit_lem_in_error(file_line, data.r_tab, NULL));
	stock_anthill(file_line, &data);
	if (D)
		debug_lem_in(&data);
	return (exit_lem_in_ok(file_line, &data));
}

int		main(int ac, char **av)
{
	int option;

	option = 0;
	if (ac >= 2)
	{
		av = get_option(ac, &av[1], &option);
		lem_in(*av, option);
	}
	else
		usage();
	if (D)
		debug_main(option);
	return (0);
}
