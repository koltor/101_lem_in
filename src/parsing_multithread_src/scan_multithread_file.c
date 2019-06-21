/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_file.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 19:47:14 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 15:46:42 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

char	*scan_line_line_for_threading(char *s, UINT id)
{
	static int	i[NB_THREAD];
	int			j;

	j = i[id];
	if (s == NULL)
	{
		i[id] = 0;
		return (NULL);
	}
	if (s[i[id]] == '\0')
		return (NULL);
	while (s[i[id]] && s[i[id]] != '\n')
		i[id]++;
	if (s[i[id]] == '\n')
		s[i[id]++] = '\0';
	return (&s[j]);
}
