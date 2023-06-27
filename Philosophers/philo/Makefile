# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seocha <seocha@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 15:57:33 by seocha            #+#    #+#              #
#    Updated: 2023/06/27 13:43:45 by seocha           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = philo

MANDATORY_DIR = ./srcs/

SRCS = philo.c simul.c utils.c error_free.c

NEW_SRCS = $(addprefix $(MANDATORY_DIR), $(SRCS))

OBJS = $(NEW_SRCS:.c=.o)

HEADER = ./includes/philo.h

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(HEADER)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re