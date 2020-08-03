# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalliar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 23:55:29 by amalliar          #+#    #+#              #
#    Updated: 2020/08/03 15:01:01 by amalliar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL      := /bin/sh
CC         := clang
CFLAGS     := -Wall -Wextra -fdiagnostics-color -g -pipe \
              -march=native -O2
INCLUDE    := -I./include -I./libft/include -I./libmlx
NAME       := cub3D
LIBFT      := ./libft/libft.a
LIBMLX     := ./libmlx/libmlx.dylib
LIBS       := -L./libft -lft -L./libmlx -lmlx -framework OpenGL -framework AppKit
SRCDIR     := src
OBJDIR     := .obj
DEPDIR     := .dep

SRCS       := src/images.c \
              src/colors.c \
	      src/graphics.c
OBJS       := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS       := $(SRCS:$(SRCDIR)/%.c=$(DEPDIR)/%.d)

# Run multiple threads.
MAKEFLAGS  = -j 4 --output-sync=recurse --no-print-directory

# Protect against make incorrectly setting 'last modified' attribute 
# when running in parallel (-j flag).
POST_COMPILE = mv -f $(DEPDIR)/$*.tmp $(DEPDIR)/$*.d && touch $@

# Define some colors for echo:
LGREEN     := \033[1;32m
WHITE      := \033[1;37m
NOC        := \033[0m

all: $(NAME)
$(NAME): $(OBJS) | $(LIBFT) $(LIBMLX)
	@echo "$(LGREEN)Linking executable $(NAME)$(NOC)"
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBS) -o $@
	@echo "Built target $(NAME)"
.PHONY: all

$(LIBFT):
	@$(MAKE) -C ./libft

$(LIBMLX):
	@$(MAKE) -C ./libmlx MAKEFLAGS= -j 1
	@cp ./libmlx/libmlx.dylib .

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -MMD -MF $(DEPDIR)/$*.tmp -c -o $@ $<
	@$(POST_COMPILE)
$(OBJDIR):
	@mkdir -p $(OBJDIR)
$(DEPDIR):
	@mkdir -p $(DEPDIR)
$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

clean:
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./libmlx clean
	@echo "$(WHITE)Removing C object files...$(NOC)"
	@-rm -rf $(OBJDIR)
	@echo "$(WHITE)Removing make dependency files...$(NOC)"
	@-rm -rf $(DEPDIR)
.PHONY: clean

fclean: clean
	@$(MAKE) -C ./libft fclean
	@-rm -f libmlx.dylib
	@echo "$(WHITE)Removing executable $(NAME)$(NOC)"
	@-rm -f $(NAME)
.PHONY: fclean

re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY: re

help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... fclean"
	@echo "... re"
.PHONY: help

# Do not include dependency files if the current goal is
# set to clean/fclean/re.
ifeq ($(findstring $(MAKECMDGOALS), clean fclean re),)
    -include $(DEPS)
endif
