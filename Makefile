# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 22:57:09 by hmoon             #+#    #+#              #
#    Updated: 2022/03/04 09:19:35 by hmoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libftprintf.a
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -f
AR			:= ar rcs

SRCS_DIR	:= ./
SRCS_NAME	:= ft_printf.c \
				parse.c util.c \
				print_cs.o print_diuxp.c
SRCS		:= $(addprefix $(SRCS_DIR),$(SRCS_NAME))
OBJS		:= ${SRCS:.c=.o}

BONUS_DIR	:= ./bonus/
BONUS_NAME	:= ft_printf_bonus.c \
				parse_bonus.c util_bonus.c \
				print_cs_bonus.c print_diuxp_bonus.c
BONUS_SRCS	:= $(addprefix $(BONUS_DIR),$(BONUS_NAME))
BONUS_OBJS	:= ${BONUS_SRCS:.c=.o}

INCLUDE		:= $(SRCS_DIR)ft_printf.h
INCLUDE_B	:= $(BONUS_DIR)ft_printf_bonus.h

ifdef PRINTF_BONUS
		OBJ_FILE = $(BONUS_OBJS)
		INCLUDE_FILE = $(INCLUDE_B)
else
		OBJ_FILE = $(OBJS)
		INCLUDE_FILE = $(INCLUDE)
endif

$(NAME) : $(OBJ_FILE) $(INCLUDE_FILE)
	$(AR) $(NAME) $(OBJ_FILE)


%.o : %.c
	$(CC) $(CFLAGS) -include $(INCLUDE_FILE) -c $< -o $@

.PHONY: all
all : $(NAME)

.PHONY : bonus
bonus :
		@make PRINTF_BONUS=1 all

.PHONY : clean
clean :
	$(RM) $(OBJS) $(BONUS_OBJS)

.PHONY : fclean
fclean : clean
	$(RM) $(NAME)

.PHONY : re
re : fclean all
