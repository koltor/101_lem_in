/*                                                              /             */
/*   new_ouput.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/06 21:27:24 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/06 22:42:24 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_putstr_2d(char **tab)
{
	UINT i;

	i = 0;
	while (tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
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
		if (i == data->lap - 1)
			break ;
		del_temp_str(&s1, &s2, NULL);
		s1 = ft_strdup(s3);
		ft_strdel(&s3);
		i++;
		s2 = ft_strdup(opt->out[i]);
	}
	data->opt = ft_strdup(s3);
	ft_strdel(&s3);
	s3 = ft_strjoin(data->bopt, data->opt);
	ft_strdel(&(data->opt));
	data->opt = ft_strdup(s3);
	del_temp_str(&s1, &s2, &s3);
}

void		get_new_lenght(char **tab, UINT (*lenght)[])
{
	UINT i;

	i = 0;
	while (tab[i])
	{
		(*lenght)[i] = ft_strlen(tab[i]);
		i++;
	}
}

void		output_final_treatment(t_data *data, t_opt *opt, UINT (*lenght)[])
{
	get_new_lenght(opt->out, lenght);
	insert_linefeed(opt, lenght, data);
	len_tab_into_data(data, lenght);
	join_output_tab(opt, data);
	data->len_opt = ft_strlen(data->opt);
	write(1, data->opt, data->len_opt);
}

void		init_opt(t_data *data, t_opt *opt, UINT (*lenght)[])
{
	opt->out = fill_buffer(data, lenght);
	opt->ants = 1;
	opt->lap = 0;
}

t_bool		new_output(t_data *data)
{
	t_opt opt;
	UINT i;
	UINT j;
	UINT lenght[data->lap];

	init_opt(data, &opt, &lenght);
	j = 0;
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
