/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/28 18:48:51 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/28 18:51:26 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	*ft_tabsub(int *pile, int size)
{
	int i;
	int *tab;

	if (!(tab = malloc(sizeof(int) * size)))
		return (NULL);
	i = -1;
	while (++i < size)
		tab[i] = pile[i];
	return (tab);
}
