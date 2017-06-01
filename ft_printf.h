/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfu <cfu@student.42.us.org>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:53:24 by cfu               #+#    #+#             */
/*   Updated: 2017/05/28 23:24:59 by cfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct		pf_type
{
	char			pound;
	char			zero;
	char			dash;
	char			space;
	char			plus;
	char			apost;
	int				min_field_wid;
	char			precision;
	char			*modifier;
	char			type;
}					pf
