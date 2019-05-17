/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 16:29:59 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int ac, char **av)
{
	int		file_fd;
	UINT	nb_fourmis;
	t_room	*room;
	t_tube	*tube;

	if (!(room = new_room(0, 0, NULL, 0)))
		return (1);
	if (!(tube = new_tube(0, 0)))
	{
		free(room);
		return (1);
	}
	if (ac == 2)
	{
		if ((file_fd = open(av[1], O_RDONLY)) < 0)
		{
			free(room);
			free(tube);
			return (1);
		}
		dprintf(1, "retour: %d\n", check_and_parse_anthill(file_fd, &room, &tube, &nb_fourmis));
		show_tube(tube);
		show_room(room);
		free_room(room);
		free_tube(tube);
		close(file_fd);
	}
	else
		usage();
	return (0);
}
