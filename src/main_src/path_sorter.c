#include "lem_in.h"

void	set_used_rooms(UINT id_tab, t_data *data)
{
	UINT i;

	i = 3;
	while (i < data->paths[id_tab][1] - 1)
	{
		data->r_tab[data->paths[id_tab][i]].used = true;
		i++;
	}
}

UINT	is_valid(UINT *tab, t_data *data)
{
	UINT i;

	i = 3;
	while (i < tab[1] - 1)
	{
		if (data->r_tab[tab[i]].used == true)
			return (0);
		i++;
	}
	return (1);
}

UINT	get_compatibe_tab_for_pid(UINT pid, t_data *data)
{
	UINT i;
	t_bool test;
	UINT ret;

	i = 0;
	test = false;
	ret = 0;
	while (data->paths[i] != NULL)
	{
		if (data->paths[i][0] == pid && test == false && is_valid(data->paths[i], data))
		{
			ret = i;
			test = true;
		}
		if (test == true && data->paths[i][0] == pid && data->paths[i][1] < data->paths[ret][1] && is_valid(data->paths[i], data))
			ret = i;
		i++;
	}
	if (test == false)
		ret = data->path_nbr + 1;
	return (ret);
}

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

void	small_path_sorter(t_data *data, UINT (*res)[], UINT max_paths, UINT pid)
{
//	UINT res[max_paths];
	UINT pnum;
	UINT tmp;
	t_bool test;

	(*res)[pid - 1] = get_compatibe_tab_for_pid(pid - 1, data);
	if ((*res)[pid - 1] != data->path_nbr)
		set_used_rooms((*res)[0], data);
	if (max_paths == pid)
		return ;
	while (pid <= max_paths)
	{
		pnum = get_pnum(pid, data);
		test = false;
		while (pnum)
		{
			if ((tmp = get_compatibe_tab_for_pid(pid, data)) != data->path_nbr + 1)
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


void	path_sorter2(t_data *data, UINT (*res)[], UINT max_paths)
{
//	UINT res[max_paths];
	UINT pid;
	UINT pnum;
	UINT tmp;
	t_bool test;

	(*res)[0] = get_compatibe_tab_for_pid(1, data);
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
			if ((tmp = get_compatibe_tab_for_pid(pid, data)) != data->path_nbr + 1)
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
		if ((*curr)[i] != path_nbr)
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

	FPF("==================================\n");
	while (tst < max_paths)
	{
		FPF("case num %u tab num %u\n", tst, (*res)[tst]);
		tst++;
	}
	FPF("==================================\n");
}

void	del_last_path(UINT (*curr)[], t_data *data, UINT max_paths, UINT index)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		data->r_tab[data->paths[(*curr)[index]][i]].used = false;
		i++;
	}
}

void	bruteforce_sorter(t_data *data, UINT max_paths)
{
	UINT res[max_paths];
	UINT curr[max_paths];
	UINT bfs;
	UINT pid;

	bfs = 0;
	pid = max_paths;
	path_sorter2(data, &curr, max_paths);
	if (check_path_found(&curr, max_paths, data->path_nbr) == max_paths)
	{
		FPF("found the greatest solution on the 1st try\n");
		return ;
	}
	while (bfs != 10)
	{
		FPF("hello\n");
		while (pid != -1)
		{
			FPF("hola\n");
			pid = del_last_path(&curr, data, max_paths, pid - 1);
			small_path_sorter(data, &curr, max_paths, pid);
			FPF("small sorter res \n");
			print_tab(&curr, max_paths);
			if (check_path_found(&curr, max_paths,data->path_nbr) == max_paths)
			{
				FPF("check les max paths\n");
				tab_cp(&curr, &res, max_paths);
				return ;
			}
			else if (check_path_found(&curr, max_paths,data->path_nbr) > check_path_found(&res, max_paths,data->path_nbr))
			{
				FPF("resize le tab\n");
				tab_cp(&curr, &res, max_paths);
			}
			pid--;
		}
		bfs++;
	}
}

/* BRUTE FORCE en partant de la fin des qu on arrive a max tab on s arrete */
