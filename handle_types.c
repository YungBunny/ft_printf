/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfu <cfu@student.42.us.org>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:47:57 by cfu               #+#    #+#             */
/*   Updated: 2017/06/01 01:59:57 by cfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



char		curr_type(char *str)
{
	int			i;
	struct pf	type;
	int			total;

	i = 0;
	total = 0;
	if (str)
	{
		structure_check();
		total = num_spec(str);
		/*function that checks structure*/
		while (str[i])
		{
			if (str[i] == '%' )
				/*send to function that creates number of structs needed*/
				i++;
			if (str[i] >= 49 && str[i] <= 57)
				type.min_field_wid = ft_atoi(str[i]);
			if (str[i] == 'd' || str[i] == 'i')
				type_int(i);
			if (str[i] == 'o' || str[i] == 'u' || str[i] == 'x' || str[i] == 'X')
				type_digi(i);
			if (str[i] == 'n')
			/*passes in place in string, so you can check the spot before 
			 * and make sure that the place before isn't negative*/
		}
	}
}

int			num_spec(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '%' && str[i + 1] == '%')
				count++;
			i++;
		}
		return (count);
	}
}

int			flags_to_mod(char *str, int i, struct fp type)
{
	if (str[i] == '#' || str[i] == '0' || str[i] == '-' || str[i] == ' ' ||
		str[i] == '+' || str[i] == ''')
	{
		flag_check(str, i, type);
		i++;
	}
	if (str[i] >= 49 && str[i] <= 57)
	{
		field_wid(str, i, type);
		i++;
	}
	if (str[i] =='.')
	{
		i++;
		if (str[i] >= 49 && str[i] <= 57)
			precision(str, i, type);
		i++;
	}
}

int			to_mod(char *str, int i, struct fp type)
{
	int		n;

	n = i;
	if (str[i] == 'h' || str[i] == 'l')
	{
		n++;
		if (str[n] == 'h')
		{
			type.modifier = ft_strdup("hh");
			return (1);
		}
		if (str[n] == 'l')
		{
			type.modifier = ft_strdup("ll");
			return (1);
		}
	}
	if (str[i] == 'j' || str[i] == 't' || str[i] == 'z' || str[i] == 'q')
	{
		if (mods(str, i, type) == 1)
			return (1);
	}
	return (0);
}

void		flag_check(char *str, int i, struct fp type)
{
	if (str[i] == '#')
		type.pound = '#';
	if (str[i] == '0')
		type.zero = '0';
	if (str[i] == '-')
		type.dash = '-';
	if (str[i] == ' ')
		type.space = ' ';
	if (str[i] == '+')
		type.plus = '+';
	if (str[i] == ''')
		type.apost = ''';
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
