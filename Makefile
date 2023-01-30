# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loris <loris@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:57:47 by loris             #+#    #+#              #
#    Updated: 2023/01/30 20:16:44 by loris            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = so_long.c so_map.c check_map.c so_win.c

LIBFT_A = libft.a
LIBFT_DIR = utils/libft/
LIBFT  = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

LIBX = ./utils/minilibx-linux/libmlx.a

OBJS = $(SRCS:.c=.o)
	
RM				= rm -f
FLAGS			= -Wall -Wextra -Werror -I.
INCLUDE			= -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz#-lmlx_Linux

%.o: %.c
	gcc $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	gcc $(FLAGS) -fsanitize=address $(OBJS) $(LIBFT) $(LIBX) $(INCLUDE) -o $(NAME)

$(OBJS): $(SRCS)
	gcc $(FLAGS) -c $(SRCS)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(NAME) $(OBJS)

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re