# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 14:08:11 by vrybalko          #+#    #+#              #
#    Updated: 2017/03/06 17:24:47 by vrybalko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

IDIR = includes/

VPATH = src

BIN_DIR = bin/

FLAGS = -Wall -Wextra -Werror -I$(IDIR) -g

LIB = libft/libft.a

SRCS = main.c					\
       read_arg.c			\
			 ft_check_arg.c	\
			 open_dir.c			\
			 sort.c					\
			 print_list.c

BINS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(BINS)
	make -C libft/
	gcc -o $(NAME) $(BINS) $(FLAGS) $(LIB)

$(BIN_DIR)%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	make -C libft/ clean
	/bin/rm -f $(BINS)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

f: all
	./$(NAME) res/test.map

r: re f
