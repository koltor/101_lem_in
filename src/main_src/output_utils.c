/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output_utils.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 13:33:27 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/08 21:30:06 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	del_temp_str(char **s1, char **s2, char **s3)
{
	if (s1)
		ft_strdel(s1);
	if (s2)
		ft_strdel(s2);
	if (s3)
		ft_strdel(s3);
}

void	stock_file_line(t_data *data, const char *s)
{
	char *s1;

	data->len_opt = ft_strlen(s);
	if (s[data->len_opt - 1] != '\n')
		s1 = "\n\n";
	else
		s1 = "\n";
	data->bopt = ft_strjoin(s, s1);
}

char	**fill_buffer(t_data *data, UINT (*lenght)[])
{
	char **buf;
	UINT i;
	UINT j;

	i = 0;
	j = 0;
//	FPF("aaaallo data->lap = %u\n", data->lap);
	if (!(buf = (char **)malloc(sizeof(char *) * (data->lap + 1))))
		f_error(ERR_MALLOC, NULL);
	buf[data->lap] = NULL;
	set_tab_zero(lenght, data->lap);
	 while (i < data->lap)
	{
	//	FPF("hey\n");
	//	if (data->ret[data->index][i])
	//	{
			//FPF("ALLLLLLOOOOO\n");
			if (!(buf[i] = ft_strnew(BUF_SIZE)))
				f_error(ERR_MALLOC, NULL);
		//	(*lenght)[j] = 0;
		//	j++;
	//	}
		i++;
	}
	return (buf);
}

void	insert_linefeed(t_opt *opt, UINT (*lenght)[], t_data *data)
{
	UINT i;

	i = 0;
//	print_tab(lenght, data->lap);
	while (i < data->lap)
	{
	//	FPF("insert line feed i = %u len = %u\n", i, (*lenght)[i]);
		opt->out[i][((*lenght)[i] - 1)] = '\n';
		i++;
	}
}

void	get_name_lenght(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (i < data->pp)
	{
		FPF("yes\n");
		j = 4;
		if (data->ret[data->index][i] != 0)
		{
			while (j < data->paths[i][1])
			{
				print_cp_tab_binary(data);
				FPF("yooo index = %u, valeur rentree dans le tab = %u\n", data->index, data->ret[data->index][i]);
				FPF("yo salle = %s\n", data->r_tab[data->ret[data->index][i]].name);
				// on peut stocker taille des chemins quand ils se font stocker dans le parsin
				data->r_tab[data->paths[i][j]].len_name =
					ft_strlen(data->r_tab[data->ret[data->index][i]].name);
				FPF("yo1\n");
				j++;
			}
		}
		i++;
	}
}
