/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfu <cfu@student.42.us.org>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:47:57 by cfu               #+#    #+#             */
/*   Updated: 2017/06/04 06:06:38 by cfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		handle_types(char *arg, ...)
{
	va_list		ap;

	va_start(ap, arg);
	if (arg)
	{
		while (*arg)
		{
			if (*arg == '%')
			{
				arg++;
				parse_it(&arg);
			}
			else
				(write(1, arg++, 1));
		}
	}
	va_end(ap);
}

void		parse_it(char **str)
{
	pf			type;
	int			total;

	total = 0;
	type.pound = '\0';
	if (*str)
	{
		check_n_place(str, &type, 0);
		null_struct(&type);
		/*total = num_spec(str);*/
		check_n_place(str, &type, 1);
		print_struct(&type);
	}
}

void		check_n_place(char **str, pf *type, int on)
{
	char	*cpy;

	cpy = *str;
	if (cpy)
	{
		flags_to_mod(&cpy, type, on);
		conversion_specifier(cpy, type, on);
	}
}

void		null_struct(pf *type)
{
	type->pound = '\0';
	type->zero = '\0';
	type->dash = '\0';
	type->space = '\0';
	type->plus = '\0';
	type->apost = '\0';
	type->min_field_wid = '\0';
	type->precision = '\0';
	type->modifier = '\0';
	type->type = '\0';

}

void		print_struct(pf *type)
{
	printf("\npound: %c\n", type->pound);
	printf("zero: %c\n", type->zero);
	printf("dash: %c\n", type->dash);
	printf("space: %c\n", type->space);
	printf("plus: %c\n", type->plus);
	printf("apost: %c\n", type->apost);
	printf("min_field_wid: %i\n", type->min_field_wid);
	printf("precision: %i\n", type->precision);
	printf("modifier: %c\n", type->modifier);
	printf("type: %c\n", type->type);
}
/*
   int			num_spec(char *str)
   {
   int		count;

   count = 0;
   if (*str)
   {
   while (**str)
   {
   if (**str == '%' && **(str + 1) == '%')
   {
   count++;
 **str + 2;
 }
 else if (**str == '%')
 {
 count++;
 *str++;
 }
 else
 *str++;
 }
 return (count);
 }
 }
 */
int			flags_to_mod(char **str, pf *type, int on)
{
	while (**str == '#' || **str == '0' || **str == '-' || **str == ' ' ||
			**str == '+' || **str == '\'')
	{
		flag_check(str, type, on);
		(*str)++;
	}
	if (**str >= 49 && **str <= 57)
		field_wid(str, type, on);
	if (**str =='.')
	{
		(*str)++;
		if (**str >= 49 && **str <= 57)
			precision(str, type, on);
	}
	to_mod(str, type, on);
	return (0);
}

int			flag_check(char **str, pf *type, int on)
{
	if (**str == '#' && on == 1)
		type->pound = '#';
	if (**str == '0' && on == 1)
		type->zero = '0';
	if (**str == '-' && on == 1)
		type->dash = '-';
	if (**str == ' ' && on == 1)
		type->space = ' ';
	if (**str == '+' && on == 1)
		type->plus = '+';
	if (**str == '\'' && on == 1)
		type->apost = '\'';
	return (1);
}

int			to_mod(char **str, pf *type, int on)
{
	if (**str == 'h')
	{
		check_h(&*str, type, on);
		return (1);
	}
	if (**str == 'l')
	{
		check_l(&*str, type, on);
		return (1);
	}
	if (**str == 'j' || **str == 't' || **str == 'z' || **str == 'q')
	{
		if (mods_jtzq(&*str, type, on) == 1)
			return (1);
	}
	return (0);
}

int			check_h(char **str, pf *type, int on)
{
	char	**cpy;

	cpy = str;
	if (**str == 'h')
	{
		(*cpy)++;
		if (**cpy == 'h')
		{
			(*str) += 2;
			if (on == 1)
				type->modifier = '1';
			return (1);
		}
		else if (on == 1)
			type->modifier = '2';
		return (1);
	}
	return (0);
}

int			check_l(char **str, pf *type, int on)
{
	char	**cpy;

	cpy = str;
	if (**str == 'l')
	{
		(*cpy)++;
		if (**cpy == 'l')
		{
			(*str) += 2;
			if (on == 1)
				type->modifier = '4';
			return (1);
		}
		if (on == 1)
			type->modifier = '3';
		return (1);
	}
	return (0);
}

int			mods_jtzq(char **str, pf *type, int on)
{
	if (on == 0)
		return (1);
	if (on == 1)
	{
		if (**str == 'j')
			type->modifier = '5';
		if (**str == 't')
			type->modifier = '6';
		if (**str == 'z')
			type->modifier = '7';
		if (**str == 'q')
			type->modifier = '8';
		return (1);
	}
	return (0);
}

void		field_wid(char **str, pf *type, int on)
{
	int		size;
	char	*convert;
	char	**cpy;

	size = 0;
	convert = NULL;
	cpy = str;
	if (cpy)
	{
		if (**cpy >= 49 && **cpy <= 57)
		{
			size = ft_atoi(*cpy);
			*cpy += ft_numlen(size);
		}
		wid_struct(size, type, on);
	}
}

int			wid_struct(int width, pf *type, int on)
{
	if (on == 1)
	{
		type->min_field_wid = width;
		return (1);
	}
	if (on == 0)
		return (1);
	return (0);
}

void		precision(char **str, pf *type, int on)
{
	int		size;
	char	*convert;
	char	**cpy;

	size = 0;
	convert = NULL;
	cpy = str;
	if (cpy)
	{
		if (**cpy >= 49 && **cpy <= 57)
		{
			size = ft_atoi(*cpy);
			*cpy += ft_numlen(size);
		}
		prec_struct(size, type, on);
	}
}

int			prec_struct(int size, pf *type, int on)
{
	if (on == 1)
	{
		type->precision = size;
		return (1);
	}
	if (on == 0)
		return (1);
	return (0);
}

int			conversion_specifier(char **str, pf *type, int on)
{
	if (**str == 'd' || **str == 'D' || **str == 'i')
		decimal(str, type, on) = 1 ? 1 : 0;
	if (**str == 'o' || **str == 'O')
		un_octal(str, type, on) = 1 ? 1 : 0;
	if (**str == 'u' || **str == 'U')
		un_decimal(str, type, on) = 1 ? 1 : 0;
	if (**str == 'x' || **str == 'X')
		un_hexadecimal(str, type, on) = 1 ? 1 : 0;
	if (**str == 'c' || **str == 'C')
		char_char(str, type, on) = 1 ? 1 : 0;
	if (**str == 's' || **str == 'S')
		strang(str, type, on) = 1 ? 1 : 0;
	else
		return (-1);
}

void		decimal(char **str, struct fp type, int on)
{
	if (**str == 'd')
		;
	if (**str == 'D')
		;
	if (**str == 'i')
		;
}

void		un_octal(char **str, struct fp type, int on)
{
	if (**str == 'o')
		;
	if (**str == 'O')
		;
}

void		un_decimal(char **str, struct fp type, int on)
{	
	if (**str == 'u')
		;
	if (**str == 'U')
		;
}

void		un_hexidecimal(char **str, struct fp type, int on)
{	
	if (**str == 'x')
		;
	if (**str == 'X')
		;
}

void		char_char(char **str, struct fp type, int on)
{	
	if (**str == 'c')
		;
	if (**str == 'C')
		;
}

void		strang(char **str, struct fp ype, int on)
{	
	if (**str == 's')
		;
	if (**str == 'S')
		;
}

int			ft_atoi(const char *str)
{
	int i;
	int sign;
	int nb;

	i = 0;
	sign = 0;
	nb = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		sign++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	if (sign == 1)
		return (-nb);
	if (sign >= 1)
		return (0);
	else
		return (nb);
}

int		ft_numlen(int n)
{
	int count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int			main(void)
{
	handle_types("printing struct %#-+88.6hh", "here");
	return (0);
}
