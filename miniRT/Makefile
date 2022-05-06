# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/25 07:34:44 by chalim            #+#    #+#              #
#    Updated: 2021/07/27 01:55:39 by chalim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS = -Werror -Wall -Wextra
AR=ar
ARFLAGS=crs
NAME=miniRT
MLX=libmlx.a
MLXPATH=./mlx
GNL = libftgnl.a
FRAMEWORK=-framework OpenGL -framework Appkit
LIB=libft.a
SRCS=\
	srcs/minirt.c \
	srcs/mlx_operation.c \
	srcs/vec3.c \
	srcs/vec3_sub.c \
	srcs/rt_reader.c \
	srcs/put_numbers.c \
	srcs/sphere.c \
	srcs/sphere2.c \
	srcs/sphere3.c \
	srcs/get_ray.c \
	srcs/color_operation.c \
	srcs/color_tracing.c \
	srcs/rt_reader_sub.c
SRCS_GNL=\
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c
SRCS_LIB=\
	Libft/ft_atoi.c \
	Libft/ft_bzero.c \
	Libft/ft_calloc.c \
	Libft/ft_isalnum.c \
	Libft/ft_isalpha.c \
	Libft/ft_isascii.c \
	Libft/ft_isdigit.c \
	Libft/ft_isprint.c \
	Libft/ft_itoa.c \
	Libft/ft_memccpy.c \
	Libft/ft_memchr.c \
	Libft/ft_memcmp.c \
	Libft/ft_memcpy.c \
	Libft/ft_memmove.c \
	Libft/ft_memset.c \
	Libft/ft_putchar_fd.c \
	Libft/ft_putendl_fd.c \
	Libft/ft_putnbr_fd.c \
	Libft/ft_putstr_fd.c \
	Libft/ft_split.c \
	Libft/ft_strchr.c \
	Libft/ft_strdup.c \
	Libft/ft_strjoin.c \
	Libft/ft_strlcat.c \
	Libft/ft_strlcpy.c \
	Libft/ft_strlen.c \
	Libft/ft_strmapi.c \
	Libft/ft_strncmp.c \
	Libft/ft_strnstr.c \
	Libft/ft_strrchr.c \
	Libft/ft_strtrim.c \
	Libft/ft_substr.c \
	Libft/ft_tolower.c \
	Libft/ft_toupper.c \
	Libft/ft_lstadd_back.c \
	Libft/ft_lstadd_front.c \
	Libft/ft_lstclear.c \
	Libft/ft_lstdelone.c \
	Libft/ft_lstiter.c \
	Libft/ft_lstlast.c \
	Libft/ft_lstmap.c \
	Libft/ft_lstnew.c \
	Libft/ft_lstsize.c
OBJ_FILES = $(SRCS:.c=.o)
OBJECTS_LIB = $(SRCS_LIB:.c=.o)
OBJECTS_GNL = $(SRCS_GNL:.c=.o)
HEADER = ./includes/

all: $(NAME)

$(NAME): ${LIB} $(MLX) $(OBJ_FILES) ${GNL}
	@$(CC) $(CFLAGS) -O3 -o $@ $(OBJ_FILES) -L. -lft -lftgnl -L${MLXPATH} -lmlx ${FRAMEWORK}

$(MLX) :
	@make -C ${MLXPATH}

${LIB}: ${OBJECTS_LIB}
	@$(AR) $(ARFLAGS) $@ $^

${GNL}: ${OBJECTS_GNL}
	@$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@ -I$(HEADER)

clean:
	@rm -rf $(OBJECTS) $(OBJECTS_LIB) ${OBJECTS_B} $(OBJECTS_GNL)

fclean:
	@rm -rf $(NAME) $(OBJ_FILES) $(OBJECTS_LIB) $(OBJECTS_GNL) ${MLX} ${LIB} ${GNL}
	@make clean -C ${MLXPATH}

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
