#include "lem_in.h"

UINT	max_paths(t_data data)
{
	if (data.r_tab[0].nb_link_tubes < data.r_tab[1].nb_link_tubes)
		return (data.r_tab[0].nb_link_tubes);
	return (data.r_tab[1].nb_link_tubes);
}

void	reset_markers(t_data *data)
{
	UINT i;

	i = 2; // attention segv si y aque start et end
	while (i < data->rooms)
	{
		if (data->r_tab[i].used == true)
			data->r_tab[i].used = false;
		i++;
	}
}

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

UINT	get_compatibe_tab_for_pid(UINT pid, t_data *data) // prend uniquement le plus petit
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

void	path_sorter2(t_data *data, UINT max_paths)
{
	UINT res[max_paths];
	UINT pid;
	UINT pnum;
	UINT tmp;
	t_bool test;

	res[0] = get_compatibe_tab_for_pid(1, data);
	if (res[0] != data->path_nbr + 1)
		set_used_rooms(res[0], data);
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
				res[pid - 1] = tmp;
				set_used_rooms(res[pid - 1], data);
				break ;
			}
			pnum--;
		}
		if (test == false)
			res[pid - 1] = data->path_nbr;
		pid++;
	}
	UINT tst = 0;
	while (tst < max_paths)
	{
		FPF("case num %u tab num %u\n", tst, res[tst]);
		tst++;
	}
} 

/* BRUTE FORCE en partant de la fin des qu on arrive a max tab on s arrete */
