/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/13 12:46:11 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/13 13:30:52 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	get_path_number(t_list *paths)
{
	UINT ret;

	ret = 0;
	while (paths)
	{
		ret++;
		paths = paths->next;
	}
	return (ret);
}

UINT	anthill_march(t_list *paths, t_data *data, char **buff, UINT ants)
{
	UINT path_nbr;

	path_nbr = data->paths_nbr;
	while (path_nbr)
	{
		
		path_nbr--;
	}
}

char	*fill_output(t_list *paths, t_data *data)
{
	char *buf;
	UINT ants;

	buf = ft_strnew(BUFF_SIZE);
	ants = data->ants;
	data->paths_nbr = get_path_number(paths);
	while (ants)
		ants -= anthill_march(paths, data, &buff, ants);
}
