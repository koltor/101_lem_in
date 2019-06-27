/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_create_struct.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:27:14 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/17 13:18:12 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_abc_zero(UINT (*abc)[128])
{
	int i;

	i = 0;
	while (i < 128)
	{
		(*abc)[i] = 0;
		i++;
	}
}

void get_abc_for_room(const char *s, UINT (*abc)[128])
{
	char	*s_cpy;
	char	*line;
	char	ret;
	int		order;

	if (!(s_cpy = ft_strdup(s)))
	{
		f_error(ERR_MALLOC, NULL);
		return ;
	}
	if (skip_ants_number(s_cpy))
		return ;
	set_abc_zero(abc);
	while ((line = scan_line_line(s_cpy)))
	{
		if ((ret = is_room(line)) == 0)
		{
			if (line[0] < 128 && order == 0)
				(*abc)[line[0]] += 1;
			order = 0;
		}
		else if (ret == -1)
			break ;
		else if (ret == 1 && order == 0)
			order = is_order(line);
	}
	scan_line_line(NULL);
	free(s_cpy);
}

void get_abc_id_for_room(UINT (*abc_id)[128], UINT abc[128])
{
	UINT id;
	UINT i;

	id = 2;
	i = 0;
	while (i < 128)
	{
		(*abc_id)[i] = id;
		id += abc[i];
		i++;
	}
}