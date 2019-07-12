/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/13 12:46:11 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/11 14:48:38 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

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
		if (i == data->lap - 1)
			break ;
		del_temp_str(&s1, &s2, NULL);
		s1 = ft_strdup(s3);
		ft_strdel(&s3);
		i++;
		s2 = ft_strdup(opt->out[i]);
	}
//	data->opt = ft_strjoin(data->bopt, s3);
	data->opt = ft_strdup(s3);
	del_temp_str(&s1, &s2, &s3);
}

void	fill_output_init(t_data *data, t_opt *opt, UINT (*lenght)[])
{
	opt->ants = 1;
	opt->lap = 1;
	get_name_lenght(data);
	opt->out = fill_buffer(data, lenght);
}

void	fill_output(t_data *data)
{
	t_opt opt;
	UINT i;
	UINT lenght[data->lap];

	fill_output_init(data, &opt, &lenght);
	while (1)
	{
		i = 0;
		while (data->ret[i])
		{
			if (opt.ants == data->ants + 1)
			{
				insert_linefeed(&opt, &lenght, data);
				len_tab_into_data(data, &lenght);
				join_output_tab(&opt, data);
				//FPF("len opt %d my len %u\n", ft_strlen(data->opt), data->len_opt);
				//UINT len = ft_strlen(data->opt);
				//write(1, &(data->opt), len);
				ft_putstr(data->opt);
				return ;
			}
			ant_march(&opt, data, i, &lenght);
			opt.ants++;
			i++;
		}
		opt.lap++;
	}
}
