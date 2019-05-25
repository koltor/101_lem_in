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

/*
** usage:
**	print the usage
*/

void	usage(void)
{
	printf("usage: lem-in [-%s][anthill_file ...]\n", LIST_OPTION);
}

/*
**usage_error:
**		print the usage and the illegal option
**	parameters
**		the tent option
*/

void	usage_option(char c)
{
	printf("ls: illegal option -- %c\n", c);
	printf("usage: lem-in [-%s][anthill_file ...]\n", LIST_OPTION);
}

/*
** f_error:
**	affect a value given in parameters in a static if the value given is upper than 0
**	if the value is 0 return the static value
**	parameters
**		a static value
**	return
**		return data given in parameters if value != 0
**		else return the value of static error
*/

void	*f_error(char value, void *data)
{
	static char errno = 0;

	if (value > 0)
		errno = value;
	else if (value == 0)
		return ((void*)&errno);
	return (data);
}

/*
** str_error:
**	transform an int_error into string
**	to help us in the comprehension
**	parameters
**		a static tab containing the string of the error
*/

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
