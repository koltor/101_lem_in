/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 18:25:18 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int ac, char **av)
{
	int		file_fd;
	t_room	*room;
	t_tube	*tube;

	if (!(room = new_room(0, 0, NULL, 0)))
		return (-1);
	if (!(tube = new_tube(0, 0)))
		return (-1);
	if (ac == 2)
	{
		if((file_fd = open(av[1], O_RDONLY)) < 0)
			return (1);
		dprintf(1, "retour: %d\n", check_and_parse_anthill(file_fd, &room, &tube));
		show_room(room);
		free_room(room);
		close(file_fd);
	}
	else
		usage();
	return (0);
}
