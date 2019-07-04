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

UINT	get_pnum(UINT pid, t_data *data)
{
	UINT i;
	UINT ret;

	i = 0;
	ret = 0;
	while (data->paths[i])
	{
		if (data->paths[i][0] == pid)
			ret++;
		i++;
	}
	return (ret);
}

UINT	get_min_pid(t_data *data, UINT max_paths)
{
	UINT i;
	UINT ret;

	i = 1;
	ret = data->paths[0][0];
	if (max_paths == 1)
		return (ret);
	while (i < max_paths)
	{
		if (data->paths[i][0] < ret)
			ret = data->paths[i][0];
		i++;
	}
	return (ret);
}

UINT	get_max_pid(t_data *data, UINT max_paths)
{
	UINT i;
	UINT ret;

	i = 1;
	ret = data->paths[0][0];
	if (max_paths == 1)
		return (ret);
	while (i <= max_paths)
	{
		if (data->paths[i][0] > ret)
			ret = data->paths[i][0];
		i++;
	}
	return (ret);
}



void	path_sorter2(t_data *data, UINT (*res)[], UINT max_paths)
{
//	UINT res[max_paths];
	UINT pid;
	UINT pnum;
	UINT tmp;
	t_bool test;
	UINT max_pid;
	UINT cell;

	cell = 1;
	(*res)[0] = get_compatible_tab_for_pid(get_min_pid(data, max_paths), data);
	if ((*res)[0] != data->path_nbr)
		set_used_rooms((*res)[0], data);
	if (max_paths == 1)
		return ;
	pid = get_min_pid(data, max_paths) + 1;
	max_pid = get_max_pid(data, max_paths);
//	FPF("pid = %u max_pid= %u\n", pid, max_pid);
	while (pid <= max_pid)
	{
		pnum = get_pnum(pid, data);
//		FPF("pnum = %u pid = %u\n", pnum, pid);
		test = false;
		while (pnum)
		{
//			FPF("allo le pid %u\n", pid);
			if ((tmp = get_compatible_tab_for_pid(pid, data)) != data->path_nbr)
			{
//				FPF("tmp = %u pid = %u cell = %u\n", tmp, pid, cell);
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
		pid++;
	}
	return ;
} 

void	print_tab(UINT (*res)[], UINT max_paths)
{
	UINT tst = 0;

	FPF("====================================================================\n");
	while (tst < max_paths)
	{
		FPF("case num %u tab num %u\n", tst, (*res)[tst]);
		tst++;
	}
	FPF("====================================================================\n");
}

UINT	del_last_path(UINT (*curr)[], t_data *data, UINT max_paths, UINT index)
{
	UINT i;

	i = 4;
	while (index)
	{
		if ((*curr)[index] != data->path_nbr)
			break ;
		index--;
	}
	while (i < data->paths[(*curr)[index]][1] - 1)
	{
	//	FPF("salle concernee %s\n", data->r_tab[data->paths[(*curr)[index]][i]].name);
		data->r_tab[data->paths[(*curr)[index]][i]].used = false;
		i++;
	}
	data->paths[(*curr)[index]][2] = USED;
//	FPF("tonper l index %u\n", index);
	return (index);
}

t_bool	small_path_sorter(t_data *data, UINT (*res)[], UINT max_paths, UINT pid)
{
//	UINT res[max_paths];
	UINT pnum;
	UINT tmp;
	t_bool test;

//	FPF("ALLO LE PID %u\n", pid);
	if (pid == 0)
		return (false);
	(*res)[pid] = get_compatible_tab_for_pid(pid + 1, data);
//	FPF("allo le compatible path %u\n", (*res)[pid]);
	if ((*res)[pid] != data->path_nbr)
	{
//		FPF("alo le segf pid = %u\n", pid);
		set_used_rooms((*res)[pid], data);
		return (true);
	}
	if (max_paths == pid + 1)
		return (true);
	while (pid <= max_paths)
	{
//		FPF("hey smps pid = %u\n", pid);
		pnum = get_pnum(pid, data);
		test = false;
		while (pnum)
		{
			if ((tmp = get_compatible_tab_for_pid(pid + 1, data)) != data->path_nbr + 1)
			{
				test = true;
				(*res)[pid - 1] = tmp;
				set_used_rooms((*res)[pid - 1], data);
				break ;
			}
			pnum--;
		}
		if (test == false)
			(*res)[pid - 1] = data->path_nbr;
		pid++;
	}
	return (true);
}

void	bruteforce_sorter(t_data *data, UINT max_paths, UINT (*res)[])
{
	UINT curr[max_paths];
	UINT bfs2;
	UINT pid;

	bfs2 = 0;
	set_tab_for_bf(&curr, data->path_nbr, max_paths);
	path_sorter2(data, &curr, max_paths);
//	print_tab(&curr, max_paths);
	if (check_path_found(&curr, max_paths, data->path_nbr) == max_paths)
	{
		tab_cp(&curr, res, max_paths);
		return ;
	}
	pid = max_paths - 1;
	while (pid != 1)
	{
		if (curr[max_paths - 1] == data->path_nbr && check_path_found(&curr, max_paths,data->path_nbr) == max_paths - 1)
			if (small_path_sorter(data, &curr, max_paths, max_paths - 1) == false)
				break ;
		if (small_path_sorter(data, &curr, max_paths, pid) == false)
			break ;
		if (check_path_found(&curr, max_paths,data->path_nbr) == max_paths)
		{
	//		FPF("tamer\n");
			tab_cp(&curr, res, max_paths);
			return ;
		}
		else if (check_path_found(&curr, max_paths,data->path_nbr) > check_path_found(res, max_paths,data->path_nbr))// || bfs2 == 0)
		{
	//		FPF("tonper\n");
			tab_cp(&curr, res, max_paths);
		}
		pid = del_last_path(&curr, data, max_paths, pid);

		bfs2++;
	}
}

UINT	get_size_valid_tab(t_data *data, UINT (*res)[], UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		if ((*res)[i] != data->path_nbr && data->paths[(*res)[i]][0] != 0)
		{
			data->paths[(*res)[i]][0] = 0;
			return (data->paths[(*res)[i]][1] - 4);
		}
		i++;
	}
	return (0);
}

UINT	get_index_valid_tab(t_data *data, UINT (*res)[], UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		if ((*res)[i] != data->path_nbr && data->paths[(*res)[i]][0] != 0)
			return (i);
		i++;
	}
	return (0);
}
