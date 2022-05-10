# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/10 15:44:11 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_DIR = build
TEST_DIR = tests
C_UNIT_DIR = $(TEST_DIR)/c_unit

SRCS := $(wildcard ft_*.c)
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

C_UNIT_SRCS := $(wildcard $(C_UNIT_DIR)/*.c)
C_UNIT_OBJS := $(C_UNIT_SRCS:%.c=$(OBJ_DIR)/%.o)

TEST_SRCS = $(wildcard $(TEST_DIR)/*_tests.c)
TEST_OBJS = $(TEST_SRCS:%.c=$(OBJ_DIR)/%.o)


MUSTAFA_FLAGS = -Werror -Wall -Wextra

.PHONY: clean test norm re retest
TARGET = libft
TEST_TARGET = run_tests

$(TARGET): $(OBJS)
	gcc $(MUSTAFA_FLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS) $(C_UNIT_OBJS) $(OBJS)
	gcc $(MUSTAFA_FLAGS) -o $@ $^

test: $(TEST_TARGET)
	./$(TEST_TARGET)

norm:
	norminette

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	gcc -c $(MUSTAFA_FLAGS) -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET)

re: clean $(TARGET)
	

retest: clean test
	

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(TEST_DIR)
	mkdir -p $(OBJ_DIR)/$(C_UNIT_DIR)
