/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output_utils.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/11 13:33:27 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 18:01:48 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	get_new_lenght(char **tab, UINT (*lenght)[])
{
	UINT i;

	i = 0;
	while (tab[i])
	{
		(*lenght)[i] = ft_strlen(tab[i]);
		i++;
	}
}

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
	if (!(buf = (char **)malloc(sizeof(char *) * (data->lap + 1))))
		f_error(ERR_MALLOC, NULL);
	buf[data->lap] = NULL;
	set_tab_zero(data->lap, lenght);
	while (i < data->lap)
	{
		if (!(buf[i] = ft_strnew(BUF_SIZE)))
			f_error(ERR_MALLOC, NULL);
		i++;
	}
	return (buf);
}

void	insert_linefeed(t_opt *opt, UINT (*lenght)[], t_data *data)
{
	UINT i;

	i = 0;
	while (i < data->lap)
	{
		opt->out[i][((*lenght)[i] - 1)] = '\n';
		i++;
	}
}
