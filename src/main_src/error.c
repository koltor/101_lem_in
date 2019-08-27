/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 16:28:01 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 11:25:45 by ocrossi     ###    #+. /#+    ###.fr     */
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
**	affect a value given in parameters in a static
**	if the value given is upper than 0
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
**	to help us for the comprehension
**	parameters
**		a static tab containing the string of the error
*/

void	str_error(int error)
{
	const char *tab[30] = {
	"Aucune erreur\n", "Un malloc a planter\n",
	"Impossible de d'ouvrir le fichier\n", "Impossible de lire le fichier\n",
	"Une Erreur est survenu\n", "2 starts dans la fourmiliere\n",
	"2 end dans la fourmiliere\n", "erreur format de tube\n",
	"Le nombre de chemin doit etre au minimum de 1\n",
	"Le nombre de salle doit etre au minimum de 2\n",
	"Le nombre de fourmis n'est pas correct\n",
	"Le nombre de fourmis n'est pas au bon format\n",
	"Manque le debut de la fourmilere\n",
	"Manque la fin de la fourmiliere\n", "erreur format de room\n",
	"2 salles ont le meme nom\n", "2 salles ont les memes coordonnées\n",
	"Attention: 2 chemins sont identiques\n",
	"Une salle est relier a elle même\n",
	"fichier vide\n", "ordre invalide\n", "overflow sur les salles\n",
	"que des commentaires dans le fichier\n",
	"salle non defini\n", "invalide positions sur les salles\n",
	"manque les fourmis\n", "aucun chemin ne peut arriver a la fin\n", "\n", "\n", "\n",
	};

	ft_putstr(tab[error]);
}
