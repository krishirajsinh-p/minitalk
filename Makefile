# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpuwar <kpuwar@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 23:03:36 by kpuwar            #+#    #+#              #
#    Updated: 2023/01/04 07:38:27 by kpuwar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SRCS = server.c client.c

EXES = $(SRCS:.c=)

CC = cc

CC_FLAGS = -Wall -Wextra -Werror

RM = rm -f

LIB = libft/libft.a

%: %.c minitalk.h
	$(CC) $(CC_FLAGS) $< $(LIB) -o $@

all: 
	make libft
	make minitalk

libft: 
	make -C libft

$(NAME): $(EXES)

clean: 
	$(RM) $(EXES)
	make clean -C libft

fclean: clean
	$(RM) $(LIB)

re: fclean all

.PHONY: libft minitalk all clean fclean re
