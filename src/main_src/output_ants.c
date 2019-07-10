#include "lem_in.h"

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

	opt->save = (*lenght)[opt->lap_cp];
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
	while (j < data->ret[i][0])
	{
		opt->room_id = data->ret[i][j];
		get_ant_move(opt, lenght, data);
		opt->lap_cp++;
		j++;
	}
}
