/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_line.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 10:23:13 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 17:15:20 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static	char	*ft_getline(const int fd, char *line)
{
	char	buff[1000 + 1];
	char	*temp;
	int		ret;

	ret = 1;
	while (!ft_strchr(line, '\n') && ret > 0)
	{
		if ((ret = read(fd, buff, 1000)) > 0)
		{
			buff[ret] = '\0';
			if (!(temp = ft_strjoin(line, buff)))
				return (NULL);
			free(line);
			line = temp;
		}
	}
	return (line);
}

static	char	*ft_split_line(char **line)
{
	int		i;
	char	*tmp;
	char	*retn_line;

	i = 0;
	tmp = *line;
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if (!(*line = ft_strsub(tmp, i + ((*line)[i] == '\n'), ft_strlen(tmp))))
	{
		free(tmp);
		return (NULL);
	}
	if (tmp[0] == '\0' || !(retn_line = ft_strsub(tmp, 0, i)))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (retn_line);
}

static	char	*ft_option_line(char *line, char option)
{
	char		*tmp;

	if (option & 1)
	{
		tmp = line;
		line = ft_strtrim(tmp);
		free (tmp);
	}
	return (line);
}

char			*get_clean_line(int fd, char option)
{
	static char *line = NULL;
	char		*retn_line;

	retn_line = NULL;
	if (fd < 0 || BUFF_SIZE < 1)
		return (NULL);
	if (line == NULL)
		line = ft_strnew(0);
	if (!(line = ft_getline(fd, line)))
		return (NULL);
	if (!(retn_line = ft_split_line(&line)))
		return (NULL);
	return (ft_option_line(retn_line, option));
}
