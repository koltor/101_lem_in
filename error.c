/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 16:28:01 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 18:16:14 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	usage(void)
{
	printf("usage: lem-in [-%s][anthill_file ...]\n", LIST_OPTION);
}

void	usage_option(char c)
{
	printf("ls: illegal option -- %c\n", c);
	printf("usage: lem-in [-%s][anthill_file ...]\n", LIST_OPTION);
}

void	*f_error(char value, void *data)
{
	static char errno = 0;

	if (value > 0)
		errno = value;
	else if (value == 0)
		return ((void*)&errno);
	return (data);
}

void	str_error(int error)
{
	const char *tab[20] = {
	"Aucune Erreur detecter",
	"Un Malloc a Planter",
	"Impossible de d'ouvrir e fichier",
	"Impossible de lire le fichier",
	"",
	"",
	"",
	"",
	"Le Nombre de Chemin doit Etre au minimum de 1",
	"Le Nombre de salle doit Etre au minimum de 2",
	"Le Nombre de Fourmis ne peut pas etre negative",
	"Le Nombre de Fourmis n'est Pas au bon format",
	"Manque Le Debut de la fourmilere",
	"Manque La Fin de la fourmiliere",
	"Manque de chemins",
	"",
	"",
	"",
	"",
	"",
	};

	dprintf(1, "%30s\n", tab[error]);
}
