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

void	stock_file_line(t_data *data, const char *s)
{
	char *s1;

//	FPF("hey stock file line |%s|\n\n", s);

	data->len_opt = ft_strlen(s);
	if (s[data->len_opt - 1] != '\n')
		s1 = "\n\n";
	else
		s1 = "\n";
	data->bopt = ft_strjoin(s, s1);
//	FPF("c0 = %c c1 = %c c2 = %c\n", s[data->len_opt - 1], s[data->len_opt - 2], s[data->len_opt - 3]);
}

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
	UINT ovf;
	UINT save;

	save = (*lenght)[lap_cp];
	(*lenght)[lap_cp] = 3 + data->r_tab[opt->room_id].len_name + count_digits(opt->ants) + (*lenght)[lap_cp];
	if ((*lenght)[lap_cp] >= BUF_SIZE)
	{
		ovf = BUF_SIZE + save;
		while (ovf <= (*lenght)[lap_cp])
		{
			r1 = ft_strnew(BUF_SIZE);
			r2 = ft_strdup(opt->out[lap_cp]);
			ft_strdel(&(opt->out[lap_cp]));
			opt->out[lap_cp] = ft_strjoin(r2, r1);
			ft_strdel(&r2);
			ft_strdel(&r1);
			ovf += BUF_SIZE;
		}
	}
	r1 = ft_strjoin("L", ft_litoa((ULL)opt->ants));
	r2 = ft_strjoin(r1, ft_strjoin("-", ft_strjoin(data->r_tab[opt->room_id].name, " ")));
	ft_strdel(&r1);
	r3 = ft_strdup(opt->out[lap_cp]);
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
	while (i < data->lap)
	{
//`printf("linefeed on en est a %s\n", &(opt->out[i][((*lenght)[i] - 2)]));
		opt->out[i][((*lenght)[i] - 1)] = '\n';
		i++;
	}
//	FPF("i = %u data->lap %u size = %u\n", i, data->lap, (*lenght)[i]);
//	opt->out[data->lap - 1][((*lenght)[i] - 1)] = '\0';
}

void	len_tab_into_data(UINT (*lenght)[], t_data *data)
{
	UINT i;

	i = 0;
	while (i < data->lap)
	{
//		FPF("line %u len %u\n", i, (*lenght)[i]);
		data->len_opt += (*lenght)[i];
		i++;
	}
//	FPF("end of len tab len output = %u\n", data->len_opt);
}

void	join_output_tab(t_opt *opt, t_data *data)
{
	UINT i;
	char *s1;
	char *s2;
	char *s3;

	i = 1;
	if (data->lap == 1)
	{
		data->opt = ft_strdup(opt->out[i - 1]);
		return ;
	}
	s1 = ft_strdup(opt->out[i - 1]);
	s2 = ft_strdup(opt->out[i]);
	while (1)
	{
		s3 = ft_strjoin(s1, s2);
	//	FPF("allo s3 %s\n", s3);
		if (i == data->lap - 1)
			break ;
		ft_strdel(&s1);
		ft_strdel(&s2);
		s1 = ft_strdup(s3);
		ft_strdel(&s3);
		i++;
		s2 = ft_strdup(opt->out[i]);
	}
//	FPF("end of join output s3 = %s\n lan prevue %u len actu %u \n", s3, data->len_opt, ft_strlen(s3));
	data->opt = ft_strjoin(data->bopt, s3);
	ft_strdel(&s1);
	ft_strdel(&s2);
	ft_strdel(&s3);
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
		//	FPF("small boucle i = %u lap = %u ants = %u\n", i, opt.lap, opt.ants);
			if (opt.ants == data->ants + 1)
			{
		//		FPF("end of treatment\n");
				insert_linefeed(&opt, &lenght, data);
				len_tab_into_data(&lenght, data);
				join_output_tab(&opt, data);
				ft_putstr(data->opt);
				//ft_putstr_2d(opt.out);
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
