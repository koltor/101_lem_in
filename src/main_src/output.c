/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/13 12:46:11 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 13:40:34 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

char	**fill_buffer(t_data *data, UINT (*lenght)[])
{
	char **buf;
	UINT i;

	i = 0;
	if (!(buf = (char **)malloc(sizeof(char *) * (data->lap + 1))))
		f_error(ERR_MALLOC, NULL);
	buf[data->lap] = NULL;
	while (i < data->lap)
	{
		(*lenght)[i] = 0;
		if (!(buf[i] = ft_strnew(BUF_SIZE)))
			f_error(ERR_MALLOC, NULL);
		i++;
	}
	return (buf);
}

void	get_ant_move(t_opt *opt, UINT (*lenght)[], t_data *data, UINT lap_cp)
{
	char *r1;
	char *r2;
	char *r3;

	(*lenght)[lap_cp] = 3 + data->r_tab[opt->room_id].len_name + count_digits(opt->ants) + (*lenght)[lap_cp];
	FPF("get ant move lap_cp = %u len = %u\n", lap_cp, (*lenght)[lap_cp]);
	r1 = ft_strjoin("L", ft_litoa((ULL)opt->ants));
	r2 = ft_strjoin(r1, ft_strjoin("-", ft_strjoin(data->r_tab[opt->room_id].name, " ")));
	ft_strdel(&r1);
//	FPF("allo get ant move r2 = %s\n", r2);
	r3 = ft_strdup(opt->out[lap_cp]);
//	FPF("allo get ant move r3 = %s\n", r3);
	ft_strdel(&(opt->out[lap_cp]));
	opt->out[lap_cp] = ft_strjoin(r3, r2);
	ft_strdel(&r2);
	ft_strdel(&r3);
}

void	ant_march(t_opt *opt, t_data *data, UINT i, UINT (*lenght)[])
{
	UINT j;
	UINT lap_cp;

	j = 1;
	lap_cp = opt->lap - 1;
//	if (i == 1)
//		FPF("hey ant march lap cp = %u i = %u\n", lap_cp);
	while (j < data->ret[i][0])
	{
		opt->room_id = data->ret[i][j];
		get_ant_move(opt, lenght, data, lap_cp);
		lap_cp++;
		j++;
	}
}

void	ft_putstr_2d(char **tab)
{
	UINT i;

	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		i++;
	}
}

void	get_name_lenght(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (data->ret[i])
	{
		j = 1;
		while (j < data->ret[i][0])
		{
			data->r_tab[data->ret[i][j]].len_name = ft_strlen(data->r_tab[data->ret[i][j]].name);
			j++;
		}
		i++;
	}
}

	void	insert_linefeed(t_opt *opt, UINT (*lenght)[], t_data *data)
{
	UINT i;

	i = 0;
	while (i < data->lap - 1)
	{
//`printf("linefeed on en est a %s\n", &(opt->out[i][((*lenght)[i] - 2)]));
		opt->out[i][((*lenght)[i] - 1)] = '\n';
		i++;
	}
//	FPF("i = %u data->lap %u size = %u\n", i, data->lap, (*lenght)[i]);
	opt->out[data->lap - 1][((*lenght)[i] - 1)] = '\0';
}

void	print_int_tab(UINT (*lenght)[], UINT lap)
{
	UINT i;

	i = 0;
	while (i < lap)
	{
		FPF("indice %u len = %u\n", i, (*lenght)[i]);
		i++;
	}
}

void	fill_output(t_data *data)
{
	t_opt opt;
	UINT i;
	UINT lenght[data->lap];

	opt.ants = 1;
	opt.lap = 1;
	get_name_lenght(data);
	opt.out = fill_buffer(data, &lenght);
	while (1)
	{
		i = 0;
		while (data->ret[i])
		{
			FPF("small boucle i = %u lap = %u ants = %u\n", i, opt.lap, opt.ants);
			if (opt.ants == data->ants + 1)
			{
				FPF("end of treatment\n");
				insert_linefeed(&opt, &lenght, data);
				print_int_tab(&lenght, data->lap);
				ft_putstr_2d(opt.out);
				return ;
			}
			//FPF("avant ant march opt lap %u\n", opt.lap);
			ant_march(&opt, data, i, &lenght);
			opt.ants++;
			i++;
		}
		opt.lap++;
	}
}

/* ne pas oublier de faire l opti pour la detection de la combinaison des plus 
 * courts chemins (ex 2 chemins a 2 lenght et 1 a 500) */
