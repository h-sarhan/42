# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/02 13:38:12 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJDIR = build

SRCS := $(wildcard *.c) 

OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

MUSTAFA_FLAGS = -Werror -Wall -Wextra

.PHONY: clean test norm
TARGET = tests

$(TARGET): $(OBJS)
	gcc -o $@ $^

test: $(TARGET)
	./$(TARGET)

norm:
	norminette $(SRCS) c_unit.h

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	gcc -c $(MUSTAFA_FLAGS) -o $@ $<

clean:
	rm -rf $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)
