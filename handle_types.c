/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfu <cfu@student.42.us.org>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:47:57 by cfu               #+#    #+#             */
/*   Updated: 2017/06/02 23:57:57 by cfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



char		curr_type(char **str)
{
	struct pf	type;
	int			total;

	i = 0;
	total = 0;
	if (*str)
	{
		structure_check(str, total, 0);
		total = num_spec(str);
		create_structs(str, total, 1);
		/*function that checks structure*/
		while (**str)
		{
			if (**str == '%' )
				/*send to function that creates number of structs needed*/
			{
				flags_to_mod(&*str, type, 1);
				**str++;
			}
			if (**str == 'd' || **str == 'i')
				type_int(*str);
			if (**str == 'o' || **str == 'u' || **str == 'x' || **str == 'X')
				type_digi(*str);
			if (**str == 'n')
			/*passes in place in string, so you can check the spot before 
			 * and make sure that the place before isn't negative*/
		}
	}
}

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

int			flags_to_mod(char **str, struct fp type, int on)
{
	if (**str == '#' || **str == '0' || **str == '-' || **str == ' ' ||
		**str == '+' || **str == ''')
	{
		flag_check(&*str, type, on);
		*str++;
	}
	if (**str >= 49 && **str <= 57)+
	{
		field_wid(&*str, type, on);
		*str++;
	}
	if (**str =='.')
	{
		*str++;
		if (**str >= 49 && **str <= 57)
			precision(&*str, type, on);
		*str++;
	}
	to_mod(&*str, type, on);
}

int			flag_check(char *str, struct fp type, int on)
{
	if (**str == '#' && on == 1)
		type.pound = '#';
	if (**str == '0' && on == 1)
		type.zero = '0';
	if (**str == '-' && on == 1)
		type.dash = '-';
	if (**str == ' ' && on == 1)
		type.space = ' ';
	if (**str == '+' && on == 1)
		type.plus = '+';
	if (**str == ''' && on == 1)
		type.apost = ''';
	return (1);
}

int			to_mod(char **str, struct fp type, int on)
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

int			check_h(char **str, struct fp type, int on)
{
	char	**cpy;

	cpy = str;
	if (**str == 'h')
	{
		**cpy++;
		if (**cpy == 'h')
		{
			**str + 2;
			if (on == 1)
				type.modifier = '1';
			return (1);
		}
		if (on == 1)
			type.modifier = '2';
		return (1);
	}
	return (0);
}

int			check_l(char **str, struct fp, type, int on)
{
	char	**cpy;

	cpy = str;
	if (**str == 'l')
	{
		**cpy++;
		if (**cpy == 'l')
		{
			**str + 2;
			if (on == 1)
				type.modifier = '4';
			return (1);
		}
		if (on == 1)
			type.modifier = '3';
		return (1);
	}
	return (0);
}

int			mods_jtzq(char **str, struct fp type, int on)
{
	if (on == 0)
		return (1);
	if (on == 1)
	{
		if (**str == 'j')
			type.modifier = '5';
		if (**str == 't')
			type.modifier = '6';
		if (**str == 'z')
			type.modifier = '7';
		if (**str == 'q')
			type.modifier = '8';
		return (1);
	}
	return (0);
}

void		field_wid(char **str, struct fp type, int on)
{
	int		size;
	char	*convert;
	char	**cpy;

	size = 0;
	convert = NULL;
	cpy = str;
	if (*str)
	{
		while (**cpy >= 49 && **cpy <= 57)
			size++;
		convert = ft_memalloc(sizeof(char *)* size);
		while (**str >= 49 && **str <= 57)
		{
			*convert = **str;
			convert++;
			*str++;
		}
		wid_struct(convert, type, on);
	}
	return (0);
}

int			wid_struct(char *convert, struct fp type, int on)
{
	int		width;

	width = ft_atoi(convert);
	if (on == 1)
	{
		type.min_field_wid = width;
		ft_strdel(width);
		return (1);
	}
	if (on == 0)
		return (1);
	return (0);
}

void		precision(char **str, struct fp type, int on)
{
	int		size;
	char	*convert;
	char	**cpy;

	size = 0;
	convert = NULL;
	cpy = str;
	if (*str)
	{
		while (**cpy >= 49 && **cpy <= 57)
			size++;
		convert = ft_memalloc(sizeof(char *)* size);
		while (**str >= 49 && **str <= 57)
		{
			*convert = **str;
			convert++;
			*str++;
		}
		pre_struct(convert, type, on);
	}
	return (0);
}

int			pre_struct(char *convert, struct fp type, int on)
{
	int		prec;

	prec = ft_atoi(convert);
	if (on == 1)
	{
		type.precision = prec;
		ft_strdel(prec);
		return (1);
	}
	if (on == 0)
		return (1);
	return (0);
}



void		structure_check(char *str)
{
	/*check if the arguments match types, %s with string*/
}

void		type_int(int i)
{

}

void		check_mod_int(char *str)
{

}

void		check_mod_digi(char *str)
{

}

	

void		handle_types(char *arg, ...)
{

	int			i;
	va_list		ap;
	char		c;

	va_start(ap, arg);
	if (arg)
	{
		while (arg[i])
		{
			/*need lots of if statements to check the structure of the input
			 * if there are quotation marks and percentage signs all in the right order
			 */
			c = curr_type(&arg);
		/*	if (c == this or that or that)
		 *	then go to this function that handles all of those cases and directs
		 *	them to sub sub functions for each case
		 */
		}
	}
	va_end(ap);
}
