# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 10:29:36 by hsarhan           #+#    #+#              #
#    Updated: 2022/08/03 13:36:38 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

# TODO: Add -Werror before submitting
CFLAGS = -Wall -Wextra  -g3 -pthread # -Werror

SRCS = error_handling.c logging.c simulation.c threads.c time.c utils.c parser.c \
		main.c philosophers.c mutexes.c

OBJS := $(SRCS:%.c=%.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

norm:
	norminette

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
