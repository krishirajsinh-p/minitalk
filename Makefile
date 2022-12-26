# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpuwar <kpuwar@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 23:03:36 by kpuwar            #+#    #+#              #
#    Updated: 2022/12/26 23:44:50 by kpuwar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SRCS = server.c client.c

OBJS = $(SRCS:.c=)

CC = cc

CC_FLAGS = -Wall -Wextra -Werror

IN_LIBFT = cd libft && make

% : %.c minitalk.h
	$(IN_LIBFT) all
	$(CC) $(CC_FLAGS) -c $< libft/libft.a -o $@

$(NAME): $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(IN_LIBFT) clean

fclean: clean
	$(IN_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
