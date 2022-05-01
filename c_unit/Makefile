# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/01 16:57:18 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJDIR = build

SRCS := $(wildcard *.c) 

OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

MUSTAFA_FLAGS = -Werror -Wall -Wextra

.PHONY: clean
TARGET = tests

$(TARGET): $(OBJS)
	gcc -o $@ $^

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	gcc -c $(MUSTAFA_FLAGS) -o $@ $<

clean:
	rm -rf $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)
