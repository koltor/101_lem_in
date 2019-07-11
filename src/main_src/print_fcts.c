#include "lem_in.h"

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

void	print_potential_paths(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	j = 0;
	FPF("nb de chemins trouves = %u\n", potential_path_counter(data));
	while (data->paths[i] != NULL)
	{
		j = 3;
		FPF("tab num %u id_path = %u size = %u\n", i, data->paths[i][0], data->paths[i][1]);
		while (j < data->paths[i][1])
		{
			FPF("salle %u name = %s\n", j, data->r_tab[data->paths[i][j]].name);
			j++;
		}
		FPF("-----------------------------------\n");
		i++;
	}
}

void	print_final_path_tab(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (data->ret[i])
	{
		j = 1;
		while (j < data->ret[i][0])
		{
			FPF("alle %s\n", data->r_tab[data->ret[i][j]].name);
			j++;
		}
		i++;
	}
	data->path_nbr = i;
}


