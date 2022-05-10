# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/10 15:32:17 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJDIR = build
C_UNIT_DIR = c_unit

SRCS := $(wildcard ft_*.c)
C_UNIT_SRCS := $(wildcard $(C_UNIT_DIR)/*.c)

OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
C_UNIT_OBJS := $(C_UNIT_SRCS:%.c=$(OBJDIR)/%.o)

UNIT_TEST_SRCS = $(wildcard *_tests.c)
UNIT_TEST_OBJS = $(UNIT_TEST_SRCS:%.c=$(OBJDIR)/%.o)

MUSTAFA_FLAGS = -Werror -Wall -Wextra

.PHONY: clean test norm re retest
TARGET = changethis
TEST_TARGET = tests

$(TARGET): $(OBJS)
	gcc $(MUSTAFA_FLAGS) -o $@ $^

$(TEST_TARGET): $(UNIT_TEST_OBJS) $(C_UNIT_OBJS) $(OBJS)
	gcc $(MUSTAFA_FLAGS) -o $@ $^

test: $(TEST_TARGET)
	./$(TEST_TARGET)

norm:
	norminette

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	gcc -c $(MUSTAFA_FLAGS) -o $@ $<

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TEST_TARGET)

re: clean $(TARGET)
	

retest: clean test
	

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/$(C_UNIT_DIR)
