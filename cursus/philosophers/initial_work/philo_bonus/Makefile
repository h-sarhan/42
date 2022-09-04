# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 10:29:36 by hsarhan           #+#    #+#              #
#    Updated: 2022/09/04 08:34:51 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra  -pthread -g3

SRCS = logging.c simulation.c simulation2.c simulation3.c time.c utils.c \
		parser.c main.c philosophers.c

OBJS := $(SRCS:%.c=%.o)

NAME = philo_bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

norm:
	norminette

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)