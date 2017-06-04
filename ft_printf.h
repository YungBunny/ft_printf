/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfu <cfu@student.42.us.org>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:53:24 by cfu               #+#    #+#             */
/*   Updated: 2017/06/04 03:46:12 by cfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct		pf_type
{
	char			pound;
	char			zero;
	char			dash;
	char			space;
	char			plus;
	char			apost;
	int				min_field_wid;
	int				precision;
	char			modifier;
	char			type;
}					pf;

void		handle_types(char *arg, ...);
void		parse_it(char **str);
void		check_n_place(char **str, pf *type, int on);
void		null_struct(pf *type);
void		print_struct(pf *type);
int			flags_to_mod(char **str, pf *type, int on);
int			flag_check(char **str, pf *type, int on);
int			to_mod(char **str, pf *type, int on);
int			check_h(char **str, pf *type, int on);
int			check_l(char **str, pf *type, int on);
int			mods_jtzq(char **str, pf *type, int on);
void		field_wid(char **str, pf *type, int on);
int			wid_struct(int width, pf *type, int on);
void		precision(char **str, pf *type, int on);
int			prec_struct(int size, pf *type, int on);
int			ft_atoi(const char *str);
int			ft_numlen(int n);

#endif
