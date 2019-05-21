/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_tube.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 16:43:14 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 16:46:05 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	get_number_of_tube(const char *s)
{
	UINT	nb_tube;
	char	*s_cpy;
	char	*line;
	char	ret;

	nb_tube = 0;
	if (!(s_cpy = ft_strdup(s)))
		return (*(UINT*)f_error(ERR_MALLOC, &nb_tube));
	scan_line_line(s_cpy);
	while ((line = scan_line_line(s_cpy)))
		if (is_room(line) == -1)
			break ;
	if (line && (ret = is_tube(line)) == 0)
		nb_tube += 1;
	if (line && ret != -1)
	{
		while ((line = scan_line_line(s_cpy)))
			if ((ret = is_tube(line)) == 0)
				nb_tube += 1;
			else if (ret == -1)
				break ;
	}
	scan_line_line(NULL);
	free(s_cpy);
	return (nb_tube);
}
