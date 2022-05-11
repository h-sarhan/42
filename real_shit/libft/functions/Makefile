# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/11 19:22:26 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean test norm re retest

OBJ_DIR = build
TEST_DIR = tests
C_UNIT_DIR = $(TEST_DIR)/c_unit

SRCS := $(wildcard ft_*.c)
C_UNIT_SRCS := $(wildcard $(C_UNIT_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*_tests.c)

OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)
C_UNIT_OBJS := $(C_UNIT_SRCS:%.c=$(OBJ_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:%.c=$(OBJ_DIR)/%.o)

NAME = libft.a
TESTS = run_tests

MUSTAFA_FLAGS = -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $@ $^
	ranlib $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	gcc -c $(MUSTAFA_FLAGS) -o $@ $<

$(TESTS): $(NAME) $(TEST_OBJS) $(C_UNIT_OBJS)
	gcc $(MUSTAFA_FLAGS) -o $@ $(TEST_OBJS) $(C_UNIT_OBJS) -L. -lft 

test: $(TESTS)
	rm -f $(TEST_DIR)/test_output/*.test
	./$(TESTS)

norm:
	norminette

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME) $(TESTS)

re: fclean $(NAME)
	
retest: fclean test
	

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(TEST_DIR)
	mkdir -p $(OBJ_DIR)/$(C_UNIT_DIR)
