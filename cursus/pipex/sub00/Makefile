# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 13:49:07 by hsarhan           #+#    #+#              #
#    Updated: 2022/06/22 11:31:22 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_SRCS =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
				ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_itoa.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c \
				ft_lstnew_bonus.c ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c \
				ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
				ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
				ft_substr.c ft_tolower.c ft_toupper.c
				
LIBFT_SRCS := $(addprefix libft/, $(LIBFT_SRCS))

PRINTF_SRCS =  conversion.c count_digits.c ft_printf.c \
				print_num_conversions.c print_numeric.c print_str_conversions.c \
				print_utils.c
				
PRINTF_SRCS := $(addprefix printf/, $(PRINTF_SRCS))

SRCS = pipex.c utils.c utils2.c error_handling.c split_args.c

BONUS_SRCS = bonus/pipex_bonus.c bonus/utils_bonus.c bonus/utils2_bonus.c \
			 bonus/error_handling_bonus.c bonus/split_args_bonus.c bonus/command_bonus.c

LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRCS:%.c=%.o)

OBJS := $(SRCS:%.c=%.o)
BONUS_OBJS := $(BONUS_SRCS:%.c=%.o)

LIBFT = libft.a
PRINTF = libftprintf.a

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g3
NAME = pipex

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(PRINTF): $(PRINTF_OBJS)
	@ar -rc $(PRINTF) $(PRINTF_OBJS)

$(LIBFT): $(LIBFT_OBJS)
	@ar -rc $(LIBFT) $(LIBFT_OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

bonus: $(OBJS) $(BONUS_OBJS) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(PRINTF) $(LIBFT) -o $(NAME)

norm:
	norminette $(SRCS) $(BONUS_SRCS) $(LIBFT_SRCS) $(PRINTF_SRCS)

clean:
	@rm -f $(OBJS) $(BONUS_OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS)

fclean: clean
	@rm -f $(NAME) $(LIBFT) $(PRINTF)
	
re: fclean $(NAME)

.PHONY: bonus norm clean fclean re all