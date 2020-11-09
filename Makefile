# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgamora <cgamora@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/24 15:15:06 by cgamora           #+#    #+#              #
#    Updated: 2020/11/09 15:07:39 by cgamora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = src/*.c
HEADER = includes/ft_ls.h
INCLUDE_LIB = libft/libft.a
INCLUDE_PRF = libft/ft_printf/libftprintf.a
FLAGS = 

all:
	@make -C  libft/ all
	@make -C  libft/ft_printf/ all
	gcc $(SRC) -g -o $(NAME) $(FLAGS) $(INCLUDE_LIB) $(INCLUDE_PRF) 

clean:
	@make -C libft/ clean
	@make -C libft/ft_printf/ clean

fclean:
	@make -C libft/ fclean
	@make -C libft/ft_printf/ fclean
	/bin/rm -f $(NAME)

re: fclean all