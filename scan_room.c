/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_room.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:42:37 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 16:45:29 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	get_number_of_room(const char *s)
{
	UINT	nb_room;
	char	*s_cpy;
	char	*line;
	char	ret;

	nb_room = 0;
	if (!(s_cpy = ft_strdup(s)))
		return (*(UINT*)f_error(ERR_MALLOC, &nb_room));
	scan_line_line(s_cpy);
	while ((line = scan_line_line(s_cpy)))
		if ((ret = is_room(line)) == 0)
			nb_room += 1;
		else if (ret == -1)
			break ;
	scan_line_line(NULL);
	free(s_cpy);
	return (nb_room);
}
