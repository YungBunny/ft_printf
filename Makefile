# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfu <cfu@student.42.us.org>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/16 18:58:18 by cfu               #+#    #+#              #
#    Updated: 2017/05/16 19:00:10 by cfu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf

SRC = handle_types.c 

OBJS = $(SRC:.c=.o)

HEADER = ./includes/

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Wextra -Werror $(SRC)
	@gcc -Wall -Wextra -Werror $(OBJS) -o $(NAME)
	@./$(NAME)

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
