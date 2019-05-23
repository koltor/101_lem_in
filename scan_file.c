/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_file.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/20 12:17:24 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/23 17:45:03 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

char	*parsing_into_line(const char *path)
{
	int		file_fd;
	char	line[9001];
	char	*tmp;
	char	*line_return;
	int		ret;

	line_return = NULL;
	if (!(tmp = ft_strnew(0)))
		return (f_error(ERR_MALLOC, NULL));
	if ((file_fd = open(path, O_RDONLY)) < 0)
		return (f_error(ERR_OPEN, NULL));
	if (read(file_fd, NULL, 0) < 0)
		return (f_error(ERR_READ, NULL));
	while ((ret = read(file_fd, line, 9000)))
	{
		line[ret] = '\0';
		if (!(line_return = ft_strjoin(tmp, line)))
			return (f_error(1, NULL));
		free(tmp);
		tmp = line_return;
	}
	return (line_return);
}

char	*scan_line_line(char *s)
{
	static int	i = 0;
	int			j;

	j = i;
	if (s == NULL)
	{
		i = 0;
		return (NULL);
	}
	if (s[i] == '\0')
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		s[i++] = '\0';
	return (&s[j]);
}
