# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 22:57:09 by hmoon             #+#    #+#              #
#    Updated: 2022/03/02 23:39:29 by hmoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libftprintf.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror

SRCS	:= ft_printf.c \
			parse.c print_cs.c \
			util.c print_diuxp.c

OBJS 	:= ft_printf.o \
			parse.o print_cs.o \
			util.o print_diuxp.o

.PHONY: all
all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

*.o : *.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : bonus
bonus : all

.PHONY : clean
clean :
	rm -f $(OBJS)

.PHONY : fclean
fclean : clean
	rm -f $(NAME)

.PHONY : re
re : fclean all
