/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/13 12:46:11 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 13:40:34 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

char	*fill_output(t_data *data)
{
	char **buf;
	UINT i;

	i = 0;
	if (!(buf = (char **)malloc(sizeof(char *) * (data->lap + 1))))
		f_error(ERR_MALLOC, NULL);
	buf[data->lap] = NULL;
	while (i < data->lap)
	{
		if (!(buf[i] = (char *)malloc(sizeof(char) * (BUF_SIZE))))
			f_error(ERR_MALLOC, NULL);
		i++;
	}
}

/* ne pas oublier de faire l opti pour la detection de la combinaison des plus 
 * courts chemins (ex 2 chemins a 2 lenght et 1 a 500) */
