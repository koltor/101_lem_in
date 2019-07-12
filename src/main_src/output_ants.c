/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output_ants.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 13:33:07 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/11 18:26:41 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	len_tab_into_data(t_data *data, UINT (*lenght)[])
{
	UINT i;

	i = 0;
	while (i < data->lap)
	{
		data->len_opt = data->len_opt + (*lenght)[i];
		i++;
	}
}

void	get_ant_move_ovf(t_opt *opt, char **s1, char **s2, UINT len)
{
	UINT ovf;

	ovf = BUF_SIZE + opt->save;
	while (ovf <= len)
	{
		*s1 = ft_strnew(BUF_SIZE);
		*s2 = ft_strdup(opt->out[opt->lap_cp]);
		ft_strdel(&(opt->out[opt->lap_cp]));
		opt->out[opt->lap_cp] = ft_strjoin(*s2, *s1);
		del_temp_str(s2, s1, NULL);
		ovf += BUF_SIZE;
	}
}

void	get_ant_move(t_opt *opt, UINT (*lenght)[], t_data *data)
{
	char *r1;
	char *r2;
	char *r3;

//	FPF("lap = %u\n", opt->lap_cp);
	opt->save = (*lenght)[opt->lap_cp];
//	FPF("opt->save %u\n", opt->save);
	(*lenght)[opt->lap_cp] = 3 + data->r_tab[opt->room_id].len_name +
			count_digits(opt->ants) + (*lenght)[opt->lap_cp];
	if ((*lenght)[opt->lap_cp] >= BUF_SIZE)
		get_ant_move_ovf(opt, &r1, &r2, (*lenght)[opt->lap_cp]);
	r1 = ft_strjoin("L", ft_litoa((ULL)opt->ants));
	r2 = ft_strjoin(r1, ft_strjoin("-",
					ft_strjoin(data->r_tab[opt->room_id].name, " ")));
	ft_strdel(&r1);
	r3 = ft_strdup(opt->out[opt->lap_cp]);
	ft_strdel(&(opt->out[opt->lap_cp]));
	opt->out[opt->lap_cp] = ft_strjoin(r3, r2);
	del_temp_str(&r2, &r3, NULL);
}

void	ant_march(t_opt *opt, t_data *data, UINT i, UINT (*lenght)[])
{
	UINT j;

	j = 1;
	opt->lap_cp = opt->lap - 1;
//	FPF("opt->lap = %u data->lap %u taille du chemin a inserer %u\n", opt->lap, data->lap, data->ret[i][0]);
	//print_final_path_tab(data);
	while (j < data->ret[i][0])
	{
	//	FPF("j = %u\n", j);
		opt->room_id = data->ret[i][j];
		get_ant_move(opt, lenght, data);
		opt->lap_cp++;
		j++;
	}
}
