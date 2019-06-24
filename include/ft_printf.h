/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   printf.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 17:05:05 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 15:15:58 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# define PFCNUM 12
# define TRUE 1
# define FALSE 0
# define FPF ft_printf

typedef union				u_type
{
	long long				i;
	unsigned long long		u;
	char					*str;
	char					c;
	long double				f;
}							t_types;

typedef	struct				s_func
{
	int						ret;
	int						lenght;
	int						negative;
	int						f_hh;
	int						f_h;
	int						f_l;
	int						f_ll;
	int						f_gl;
	int						precision;
	int						precision_size;
	int						minus;
	int						plus;
	int						hash;
	int						zero;
	int						space;
	int						width;
	int						width_size;
	int						cpt;
	t_types					type;
	void					(*f[PFCNUM])(va_list ap, struct s_func *tab);
	char					tab_type[PFCNUM];
	char					*output;
}							t_func;

int							ft_printf(const char *format, ...);
char						*ft_printfloat(long double f, size_t precision,
			char *r);
char						*base_managment(unsigned long long nb, int base);
void						print_bytes(char *str);
void						scan_format(char *format, t_func *tab);
void						scan_options(char **format, t_func *tab);
void						goto_type(char **format);
void						check_option_compatibility(t_func *tab);
void						end_pf(char **r1, char **r2, char **r3);
int							ft_getsize(char **format);
char						*ft_zero(char **str);
void						ft_hash(t_func *tab);
void						ft_plus(t_func *tab);
void						ft_space(t_func *tab);
void						ft_precision(t_func *tab);
void						ft_precision2(t_func *tab, int rab, int i);
void						ft_launch_options(t_func *tab);
void						ft_width(t_func *tab);
void						ft_width2(t_func *tab, char *r);
void						ft_width_complicated(t_func *tab);
int							ft_check_type(char c);
void						ft_print_int(va_list ap, t_func *tab);
void						ft_print_unsigned_int(va_list ap, t_func *tab);
void						ft_print_octal(va_list ap, t_func *tab);
void						ft_print_char(va_list ap, t_func *tab);
void						ft_print_string(va_list ap, t_func *tab);
void						ft_print_binary(va_list ap, t_func *tab);
void						ft_print_hexa(va_list ap, t_func *tab);
void						ft_print_hexac(va_list ap, t_func *tab);
void						ft_print_fl(va_list ap, t_func *tab);
void						ft_print_percent(va_list ap, t_func *tab);
//int							ft_atoi(char *str);
char						*ft_litoa(unsigned long long n);
int							ft_count_lnumber(unsigned long long n);
char						*ft_strdup(const char *s1);
char						*ft_strjoin(char const *s1, char const *s2);
size_t						ft_strlen(const char *s);
char						*ft_strnew(size_t t);
void						ft_putchar(char c);
//void						ft_putstr(char *str);
char						*ft_strcapitalize(char *str);
char						*ft_strcat(char *s1, const char *s2);
void						ft_strdel(char **as);
char						*ft_strsub(char const *s, unsigned int start,
		size_t len);
char						*ft_strncpy(char *dest, const char *src,
		size_t len);
void						scan_bout_de_scotch2(char **r3, int *cpt);
void						ft_width2_space(t_func *tab, char *r, char *tmp);
void						check_option_compatibility3(t_func *tab);
void						check_option_compatibility4(t_func *tab);
void						negative_ints1(t_func *tab, unsigned long long *nb);
void						negative_ints2(t_func *tab, char *tmp);
void						negative_floats(t_func *tab, char *tmp);

#endif
