/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfu <cfu@student.42.us.org>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:47:57 by cfu               #+#    #+#             */
/*   Updated: 2017/05/17 00:29:28 by cfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



char		curr_type(char *str)
{
	int		i;
	int		mod;

	i = 0;
	mod = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '%' )
				i++;
			if (str[i] == 'd' || str[i] == 'i')
				type_int(i);
			/*passes in place in string, so you can check the spot before 
			 * and make sure that the place before isn't negative*/
		}
	}
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
