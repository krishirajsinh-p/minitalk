# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpuwar <kpuwar@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 23:03:36 by kpuwar            #+#    #+#              #
#    Updated: 2023/01/18 14:30:46 by kpuwar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SRCS = server.c client.c

EXES = $(SRCS:.c=)

SRCS_B = server_bonus.c client_bonus.c

EXES_B = $(SRCS_B:.c=)

CC = cc

CC_FLAGS = -Wall -Wextra -Werror

RM = rm -f

LIB = libft/libft.a

$(NAME): all

all: $(SRCS) minitalk.h
	make -C libft
	$(CC) $(CC_FLAGS) server.c $(LIB) -o server
	$(CC) $(CC_FLAGS) client.c $(LIB) -o client

clean: 
	$(RM) $(EXES)
	make clean -C libft

fclean: clean
	$(RM) $(LIB)

re: fclean all

bonus: $(SRCS_B) minitalk_bonus.h
	make -C libft
	$(CC) $(CC_FLAGS) server_bonus.c $(LIB) -o server_bonus
	$(CC) $(CC_FLAGS) client_bonus.c $(LIB) -o client_bonus

clean_b: 
	$(RM) $(EXES_B)
	make clean -C libft

fclean_b: clean_b
	$(RM) $(LIB)

re_b: fclean_b bonus

.PHONY: minitalk all clean fclean re bonus clean_b fclean_b re_b
