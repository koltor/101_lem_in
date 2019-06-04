/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_file.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/20 12:17:24 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/04 22:14:25 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
** parsing_into_line:
**	transform the file give in parameters into string
**	parameters
**		need the path of a file
**	variables
**		INT 	file_fd stock the return value after open the path
**		CHAR	line is a fixe_memory (need for read)
**		char	tmp is a tampon
**		char	line_return is the line return at the end of the function
**		ret		stock the return of read
**	return value
**		the file_line and affect a value of error if a problem occurd
*/

char	*parsing_into_line(const char *path)
{
	int		file_fd;
	char	line[9001];
	char	*tmp;
	char	*line_return;
	int		ret;

	line_return = NULL;
	if ((file_fd = open(path, O_RDONLY)) < 0)
		return (f_error(ERR_OPEN, NULL));
	if (read(file_fd, NULL, 0) < 0)
		return (f_error(ERR_READ, NULL));
	if (!(tmp = ft_strnew(0)))
		return (f_error(ERR_MALLOC, NULL));
	while ((ret = read(file_fd, line, 9000)))
	{
		line[ret] = '\0';
		if (!(line_return = ft_strjoin(tmp, line)))
			return (f_error(1, NULL));
		free(tmp);
		tmp = line_return;
	}
	if (line_return == NULL)
		free(tmp);
	return (line_return);
}

/*
** scan_line_line:
**	transform the \n of the string into \0 a give line after line
**	for each call
**	parameters
**		need a string containing the file_line
**	variables
**		INT for moving on the string
**		INT for keep a previous position
**	return value
**		a positon on the file_line
*/

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
