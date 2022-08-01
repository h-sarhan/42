# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 20:40:06 by hsarhan           #+#    #+#              #
#    Updated: 2022/07/31 14:59:07 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g3
CC = cc

NAME = push_swap
LIBFT = libft.a
PRINTF = libftprintf.a

SRCS =	stack_moves/swap.c stack_moves/push.c stack_moves/rotate.c stack_moves/reverse_rotate.c \
		stack.c utils.c chunk.c small_sort.c parser.c ft_atol.c sort.c parser2.c

LIBFT_SRCS = ft_strchr.c ft_split.c ft_strtrim.c ft_bzero.c ft_strnstr.c ft_strmapi.c ft_isprint.c ft_atoi.c ft_strdup.c \
			ft_tolower.c ft_toupper.c ft_substr.c ft_striteri.c ft_memchr.c ft_putnbr_fd.c ft_strlcpy.c ft_itoa.c \
			ft_memset.c ft_calloc.c ft_strlen.c ft_putchar_fd.c ft_isascii.c ft_strlcat.c ft_putendl_fd.c ft_memcmp.c \
			ft_isdigit.c ft_strrchr.c ft_putstr_fd.c ft_isalpha.c ft_strncmp.c ft_isalnum.c ft_memcpy.c ft_memmove.c \
			ft_strjoin.c ft_lstadd_front_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstclear_bonus.c \
			ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c
			

LIBFT_SRCS := $(addprefix libft/, $(LIBFT_SRCS))		   

PRINTF_SRCS = conversion.c print_str_conversions.c \
			print_num_conversions.c count_digits.c ft_printf.c \
			print_utils.c print_numeric.c
PRINTF_SRCS := $(addprefix printf/, $(PRINTF_SRCS))		   
GNL_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c


OBJS := $(SRCS:%.c=%.o)
LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRCS:%.c=%.o)
GNL_OBJS := $(GNL_SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(GNL_OBJS) $(OBJS) push_swap.o
	$(CC) $(CFLAGS) push_swap.o $(OBJS)  $(GNL_OBJS) $(PRINTF) $(LIBFT)   -o $@

$(LIBFT): $(LIBFT_OBJS)
	ar -rcs $@ $^

$(PRINTF): $(PRINTF_OBJS)
	ar -rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

checker: $(LIBFT) $(PRINTF) $(GNL_OBJS) $(OBJS) checker.o
	$(CC) $(CFLAGS) checker.o $(OBJS)  $(GNL_OBJS) $(PRINTF) $(LIBFT)   -o $@

bonus: checker

norm:
	norminette $(LIBFT_SRCS) $(PRINTF_SRCS) $(SRCS) $(GNL_SRCS) libft/libft.h printf/ft_printf.h push_swap.h

clean:
	rm -f $(OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS) $(LIBFT) $(PRINTF) $(GNL_OBJS) push_swap.o checker.o

fclean: clean
	rm -f $(NAME) checker

re: fclean $(NAME)