/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 14:47:26 by matheme     ###    #+. /#+    ###.fr     */
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

static t_bool	exit_lem_in_error(char *l, char *l2, t_room *r, t_tube *t)
{
	if (l)
		free(l);
	if (l2)
		free(l2);
	if (r)
		free(r);
	if (t)
		free(t);
	return (false);
}

/*
** exit_lem_in_ok:
**	parameters
**		need elements for free
**	return value
**		return true
*/

static t_bool	exit_lem_in_ok(char *file_line, t_data *data)
{
	free(file_line);
	free(data->t_tab);
	free_room(data->r_tab, data->rooms);
	ft_strdel(&(data->opt));
	ft_strdel(&(data->bopt));
	del_2d_int_tab(data->ret);
	del_2d_int_tab(data->paths);
	return (true);
}

static t_bool	lem_in2(t_data *data, int option, char *fine)
{
	get_abc_for_room(fine, &data->abc.abc_len);
	get_abc_id_for_room(&data->abc.abc_start, data->abc.abc_len);
	get_abc_id_for_room(&data->abc.abc_id, data->abc.abc_len);
	if ((O_M && stock_anthill_for_threading(fine, data)) ||
	(!O_M && stock_anthill(fine, data)))
		return (exit_lem_in_error(fine, data->bopt, data->r_tab, data->t_tab));
	if (browse_map(data))
		return (exit_lem_in_error(fine, data->bopt, data->r_tab, data->t_tab));
	if (!generic_sorter(data))
	{
		return (exit_lem_in_error(fine, data->bopt, data->r_tab, NULL));
		free_tab_turn(data->t_tab, data->tubes);
	}
	free_tab_turn(data->t_tab, data->tubes);
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

t_bool			lem_in(const char *path, int option)
{
	char	*f_line;
	t_data	data;

	if (!(f_line = parsing_into_line(path)))
	{
		if (*(char*)f_error(0, NULL) == 0)
			f_error(ERR_EMPTY_FILE, NULL);
		return (exit_lem_in_error(f_line, NULL, NULL, NULL));
	}
	stock_file_line(&data, f_line);
	if ((data.rooms = get_number_of_room(f_line)) < 2)
		return (exit_lem_in_error(f_line, data.bopt, NULL, NULL));
	if ((data.tubes = get_number_of_tube(f_line)) < 1)
		return (exit_lem_in_error(f_line, data.bopt, NULL, NULL));
	if (!(data.r_tab = create_room(data.rooms)))
		return (exit_lem_in_error(f_line, data.bopt, NULL, NULL));
	if (!(data.t_tab = create_tube(data.tubes)))
		return (exit_lem_in_error(f_line, data.bopt, data.r_tab, NULL));
	if (lem_in2(&data, option, f_line))
		return (false);
	O_D || O_I ? global_info(&data) : 0;
	O_D ? debug_lem_in(&data) : 0;
	O_V ? main_visualisateur(data) : 0;
	O_L ? FPF("here is the number of lines on output : %u\n", data.lap) : 0;
	return (exit_lem_in_ok(f_line, &data));
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

int				main(int ac, char **av)
{
	int				option;

	if (ac >= 2)
	{
		av = get_option(ac - 1, &av[1], &option);
		if (lem_in(*av, option) && !O_D && !O_I)
			str_error(*(char*)f_error(0, NULL));
	}
	else
		usage();
	if (O_D || O_I)
		debug_main(option);
	return (0);
}
