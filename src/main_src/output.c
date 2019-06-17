/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/13 12:46:11 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/17 19:19:21 by ocrossi     ###    #+. /#+    ###.fr     */
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


char	*fill_output(t_list *paths, t_data *data)
{
	char *buf;
	UINT ants;

	ants = data->ants;
	if (ants > data->path_nbr)
	{

	}
}
