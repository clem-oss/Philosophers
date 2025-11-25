# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csalaun <csalaun@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/29 23:09:57 by csalaun           #+#    #+#              #
#    Updated: 2025/11/25 14:13:13 by csalaun          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FILES = main.c utils.c init.c error.c monitor.c routine.c free.c

SRCS = $(addprefix srcs/, $(FILES))
OBJ = $(SRCS:srcs/%.c=build/%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I./includes/

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDE) -o $(NAME)
	@echo "\033[92m[philo] [✔] $(NAME) successfully compiled\033[0m"

build/%.o: srcs/%.c
	@mkdir -p build
	@$(CC) $(CFLAGS) $(INCLUDE) -c  $< -o $@
	@echo "\033[96m[philo] [🔧] Compiled $<\033[0m"

clean:
	@rm -rf build
	@echo "\033[93m[philo] [🧹] Cleaned build directory\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[91m[philo] [🔥] Removed binary: $(NAME)\033[0m"

re: fclean all