/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_sorter.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/24 20:32:50 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/25 16:31:27 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	path_sorter2_1(t_data *data, UINT (*res)[], UINT cell, UINT pid)
{
	UINT pnum;
	t_bool test;
	UINT tmp;

	pnum = get_pnum(pid, data);
	test = false;
	while (pnum)
	{
		if ((tmp = get_compatible_tab_for_pid(pid, data)) != data->path_nbr)
		{
			test = true;
			(*res)[cell] = tmp;
			set_used_rooms((*res)[cell], data);
			cell++;
			break ;
		}
		pnum--;
	}
	if (test == false)
		(*res)[pid - 1] = data->path_nbr;
	return (cell);
}

void	path_sorter2(t_data *data, UINT (*res)[], UINT max_paths, UINT cell)
{
	UINT pid;
	UINT pnum;
	UINT tmp;
	t_bool test;
	UINT max_pid;

	(*res)[0] = get_compatible_tab_for_pid(get_min_pid(data, max_paths), data);
	if ((*res)[0] != data->path_nbr)
		set_used_rooms((*res)[0], data);
	if (max_paths == 1)
		return ;
	pid = get_min_pid(data, max_paths) + 1;
	max_pid = get_max_pid(data, max_paths);
	while (pid <= max_pid)
	{
		cell = path_sorter2_1(data, res, cell, pid);
		pid++;
	}
	return ;
} 

UINT	del_last_path(UINT (*curr)[], t_data *data, UINT max_paths)
{
	UINT i;
	UINT index;

	i = 4;
	index = data->pid;
	while (index)
	{
		if ((*curr)[index] != data->path_nbr)
			break ;
		index--;
	}
	while (i < data->paths[(*curr)[index]][1] - 1)
	{
		data->r_tab[data->paths[(*curr)[index]][i]].used = false;
		i++;
	}
	data->paths[(*curr)[index]][2] = USED;
	return (index);
}

void	browse_potential_tabs(UINT pnum, t_data *data, UINT (*res)[], t_bool *test)
{
	UINT tmp;

	while (pnum)
	{
		if ((tmp = get_compatible_tab_for_pid(data->pid + 1, data)) != data->path_nbr + 1)
		{
			*test = true;
			(*res)[data->pid - 1] = tmp;
			set_used_rooms((*res)[data->pid - 1], data);
			return ;
		}
		pnum--;
	}
}

t_bool	small_path_sorter(t_data *data, UINT (*res)[], UINT max_paths)
{
	UINT pnum;
	t_bool test;
	UINT pid_cp;

	pid_cp = data->pid;
	(*res)[pid_cp] = get_compatible_tab_for_pid(pid_cp + 1, data);
	if ((*res)[pid_cp] != data->path_nbr)
	{
		set_used_rooms((*res)[pid_cp], data);
		return (true);
	}
	if (max_paths == pid_cp + 1)
		return (true);
	while (pid_cp <= max_paths)
	{
		pnum = get_pnum(pid_cp, data);
		test = false;
		browse_potential_tabs(pnum, data, res, &test);
		if (test == false)
			(*res)[pid_cp - 1] = data->path_nbr;
		data->pid++;
		pid_cp++;
	}
	return (true);
}

UINT	init_bf(UINT (*curr)[], UINT max_paths, t_data *data, UINT (*res)[])
{
	UINT cell;

	cell = 1;
	set_tab_for_bf(curr, data->path_nbr, max_paths);
	path_sorter2(data, curr, max_paths, cell);
	if (check_path_found(curr, max_paths, data->path_nbr) == max_paths)
	{
		tab_cp(curr, res, max_paths);
		return (1);
	}
	return (0);
}

void	bruteforce_sorter(t_data *data, UINT max_paths, UINT (*res)[])
{
	UINT curr[max_paths];
	UINT cell;

	cell = 1;
	if (init_bf(&curr, max_paths, data, res) == 1)
		return ;
	data->pid = max_paths - 1;
	while (data->pid != 1)
	{
		if (curr[max_paths - 1] == data->path_nbr && check_path_found(&curr, max_paths,data->path_nbr) == max_paths - 1)
			if (data->pid == 0 || small_path_sorter(data, &curr, max_paths) == false)
				break ;
		if (data->pid == 0 || small_path_sorter(data, &curr, max_paths) == false)
			break ;
		if (check_path_found(&curr, max_paths,data->path_nbr) == max_paths)
		{
			tab_cp(&curr, res, max_paths);
			return ;
		}
		else if (check_path_found(&curr, max_paths,data->path_nbr) > check_path_found(res, max_paths,data->path_nbr))
			tab_cp(&curr, res, max_paths);
		data->pid = del_last_path(&curr, data, max_paths);
	}
}
