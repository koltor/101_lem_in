/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_output.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/26 17:51:29 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 11:43:11 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	join_output_tab_norm(t_data *data, char **s1, char **s2, char **s3)
{
	data->opt = ft_strdup(*s3);
	ft_strdel(s3);
	*s3 = ft_strjoin(data->bopt, data->opt);
	ft_strdel(&(data->opt));
	data->opt = ft_strdup(*s3);
	del_temp_str(s1, s2, s3);
}

void	join_output_tab(t_opt *opt, t_data *data)
{
	UINT	i;
	char	*s1;
	char	*s2;
	char	*s3;

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
	join_output_tab_norm(data, &s1, &s2, &s3);
}

void	output_final_treatment(t_data *data, t_opt *opt, UINT (*lenght)[])
{
	get_new_lenght(opt->out, lenght);
	insert_linefeed(opt, lenght, data);
	len_tab_into_data(data, lenght);
	join_output_tab(opt, data);
	del_output(opt);
	data->len_opt = ft_strlen(data->opt);
	write(1, data->opt, data->len_opt);
}

void	init_opt(t_data *data, t_opt *opt, UINT (*lenght)[])
{
	opt->out = fill_buffer(data, lenght);
	opt->ants = 1;
	opt->lap = 0;
}

t_bool	new_output(t_data *data)
{
	t_opt	opt;
	UINT	i;
	UINT	lenght[data->lap];

	init_opt(data, &opt, &lenght);
	while (opt.ants != data->ants + 1)
	{
		i = 0;
		while (i < data->pp)
		{
			if (opt.ants == data->ants + 1)
				break ;
			if (data->ret[data->index][i])
			{
				ant_march(&opt, data, i, &lenght);
				data->ret[data->index][i]--;
				opt.ants++;
			}
			i++;
		}
		opt.lap++;
	}
	output_final_treatment(data, &opt, &lenght);
	return (true);
}
