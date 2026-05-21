# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 15:20:05 by seojulee          #+#    #+#              #
#    Updated: 2023/01/26 13:31:54 by seojulee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
CC		= cc
CFLAGS	= -c -Wall -Wextra -Werror
AR		= ar -rcs
RM		= rm -f

SRCS	= ft_printf.c ft_printf_utils.c ft_printf_specifier.c

OBJS	= $(SRCS:.c=.o)

all	: 		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

.c.o :
			$(CC) $(CFLAGS) $< -o $@ -I ft_printf.h

clean :
			$(RM) $(OBJS)

fclean : 	clean
			$(RM) $(NAME)

re : 		fclean all

.PHONY : all clean fclean re bonus
