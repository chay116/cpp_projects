# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/09 06:18:55 by chalim            #+#    #+#              #
#    Updated: 2021/09/03 07:47:56 by chalim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang++
CFLAGS =-Wall -Wextra -Werror -std=c++98
NAME = test
SRCS = \
	main.cpp
OBJ = $(SRCS:.cpp=.o)
HEADER = ./includes

all: ${NAME}

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $^ -o $@ -I$(HEADER)

clean:
	@rm -rf $(OBJ)

fclean:
	@make clean
	@rm -rf ${NAME}

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
