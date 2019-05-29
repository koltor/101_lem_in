/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 18:05:22 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** exit_lem_in_error:
**	parameters
**		need elements for free
**	return value
**		return false
*/

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

/*
** exit_lem_in_ok:
**	parameters
**		need elements for free
**	return value
**		return true
*/

t_bool	exit_lem_in_ok(char *file_line, t_data *data)
{
	free(file_line);
	free(data->t_tab);
	free_room(data->r_tab, data->rooms);
	return (true);
}

/*
** lem_in:
**	parameters
**		the path of the file given in parameters
**		the option given
**	variable
**		char *file_line to stock the file after transform in string
**		struct data to stock it
**	return value
**		return true if the file_line is in good format
**		and enough information collect
**		otherwise return false
*/

t_bool	lem_in(const char *path, int option)
{
	char	*file_line;
	t_data	data;

	if (!(file_line = parsing_into_line(path)))
	{
		if (*(char*)f_error(0, NULL) == 0)
			f_error(ERR_EMPTY_FILE, NULL);
		return (exit_lem_in_error(NULL, NULL, NULL));
	}
	if ((data.rooms = get_number_of_room(file_line)) < 2)
		return (exit_lem_in_error(file_line, NULL, NULL));
	if ((data.tubes = get_number_of_tube(file_line)) < 1)
		return (exit_lem_in_error(file_line, NULL, NULL));
	if (!(data.r_tab = create_room(data.rooms)))
		return (exit_lem_in_error(file_line, NULL, NULL));
	if (!(data.t_tab = create_tube(data.tubes)))
		return (exit_lem_in_error(file_line, data.r_tab, NULL));
	stock_anthill(file_line, &data);
	// get nodes
	if (D)
		debug_lem_in(&data);
	return (exit_lem_in_ok(file_line, &data));
}

/*
**main:
**	first function call after exect the programm
**	parameters
**		int		ac	number of argument
**		char	**a	arguments
**	variable
**		int for stock options
*/

int		main(int ac, char **av)
{
	int option;

	option = 0;
	if (ac >= 2)
	{
		av = get_option(ac - 1, &av[1], &option);
		lem_in(*av, option);
	}
	else
		usage();
	if (D)
		debug_main(option);
	return (0);
}
