/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_sorter.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/24 20:32:50 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 22:03:08 by ocrossi     ###    #+. /#+    ###.fr     */
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


void	path_sorter2(t_data *data, UINT (*res)[], UINT max_paths)
{
//	UINT res[max_paths];
	UINT pid;
	UINT pnum;
	UINT tmp;
	t_bool test;

	(*res)[0] = get_compatible_tab_for_pid(1, data);
	if ((*res)[0] != data->path_nbr)
		set_used_rooms((*res)[0], data);
	if (max_paths == 1)
		return ;
	pid = 2;
	while (pid <= max_paths)
	{
		pnum = get_pnum(pid, data);
		test = false;
		while (pnum)
		{
			if ((tmp = get_compatible_tab_for_pid(pid, data)) != data->path_nbr + 1)
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
	return ;
} 

UINT	check_path_found(UINT (*curr)[], UINT max_paths, UINT path_nbr)
{
	UINT res;
	UINT i;

	res = 0;
	i = 0;
	while (i < max_paths)
	{
		if ((*curr)[i] < path_nbr)
			res++;
		i++;
	}
	return (res);
}

void	tab_cp(UINT (*curr)[], UINT (*res)[], UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		(*res)[i] = (*curr)[i];
		i++;
	}
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
	FPF("tonper l index %u\n", index);
	return (index);
}

t_bool	small_path_sorter(t_data *data, UINT (*res)[], UINT max_paths, UINT pid)
{
//	UINT res[max_paths];
	UINT pnum;
	UINT tmp;
	t_bool test;

	FPF("ALLO LE PID %u\n", pid);
	if (pid == 0)
		return (false);
	(*res)[pid] = get_compatible_tab_for_pid(pid + 1, data);
	FPF("allo le compatible path %u\n", (*res)[pid]);
	if ((*res)[pid] != data->path_nbr)
	{
		FPF("alo le segf pid = %u\n", pid);
		set_used_rooms((*res)[pid], data);
		return (true);
	}
	if (max_paths == pid + 1)
		return (true);
	while (pid <= max_paths)
	{
		FPF("hey smps pid = %u\n", pid);
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

void	bruteforce_sorter(t_data *data, UINT max_paths)
{
	UINT res[max_paths];
	UINT curr[max_paths];
	UINT bfs;
	UINT bfs2;
	UINT pid;

	bfs = 0;
	bfs2 = 0;
	path_sorter2(data, &curr, max_paths);
	FPF("traitement du debut\n");
	print_tab(&curr, max_paths);
	if (check_path_found(&curr, max_paths, data->path_nbr) == max_paths)
	{
		FPF("found the greatest solution on the 1st try\n");
		return ;
	}
		pid = max_paths - 1;
		while (pid != 1)
		{
			FPF("bfs be like %u\n", bfs);
			pid = del_last_path(&curr, data, max_paths, pid);
			FPF("hola pid = %u\n", pid);
			if (small_path_sorter(data, &curr, max_paths, pid) == false)
				break ;
			if (curr[max_paths - 1] == data->path_nbr && check_path_found(&curr, max_paths,data->path_nbr) == max_paths - 1)
				if (small_path_sorter(data, &curr, max_paths, max_paths - 1) == false)
					break ;

			print_tab(&curr, max_paths);
			if (check_path_found(&curr, max_paths,data->path_nbr) == max_paths)
			{
				FPF("check les max paths\n");
				tab_cp(&curr, &res, max_paths);
				return ;
			}
			else if (check_path_found(&curr, max_paths,data->path_nbr) > check_path_found(&res, max_paths,data->path_nbr) || bfs2 == 0)
			{
				FPF("BOJOUR le ELSE IF\n");\
				tab_cp(&curr, &res, max_paths);
				FPF("apres traitement\n");
				print_tab(&res, max_paths);
				print_tab(&curr, max_paths);
			}
			bfs2++;
		}
	FPF("end of bruteforce \n");
	print_tab(&res, max_paths);
}

/* BRUTE FORCE en partant de la fin des qu on arrive a max tab on s arrete */
