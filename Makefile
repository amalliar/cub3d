# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalliar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 23:55:29 by amalliar          #+#    #+#              #
#    Updated: 2020/09/13 19:54:40 by amalliar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL      := /bin/sh
CC         := clang
CFLAGS     := -Wall -Wextra -fdiagnostics-color -g -pipe \
              -march=native -O2
INCLUDE    := -I./include -I./libft/include -I./libmlx -I./libsdl2/include
NAME       := cub3D
LIBFT      := ./libft/libft.a
LIBMLX     := ./libmlx/libmlx.dylib
LIBS       := -L./libft -lft -L./libmlx -lmlx -framework OpenGL -framework AppKit -L./libsdl2 -lSDL2-2.0.0
SRCDIR     := src
OBJDIR     := .obj
DEPDIR     := .dep

SRCS       := src/attempt_item_pickup.c \
              src/button_press_handler.c \
              src/button_release_handler.c \
              src/colors.c \
              src/exit_failure.c \
              src/expose_handler.c \
              src/graphics.c \
              src/graphics_2.c \
              src/graphics_3.c \
              src/item_pickup.c \
              src/item_pickup_2.c \
              src/key_press_handler.c \
              src/key_release_handler.c \
	      src/load_audio.c \
              src/load_scene.c \
              src/load_scene_2.c \
              src/load_textures.c \
              src/mlx_image_to_bmp_file.c \
              src/object_collision.c \
              src/parse_map.c \
              src/parse_map_2.c \
              src/process_interact_request.c \
              src/process_key_states.c \
              src/process_key_states_2.c \
              src/process_mouse_motion.c \
              src/process_physics.c \
              src/render_floor_and_ceiling.c \
              src/render_hud.c \
	      src/render_hud_2.c \
              src/render_scene.c \
              src/render_sprites.c \
              src/render_walls.c \
              src/render_walls_2.c \
              src/render_walls_3.c \
              src/switch_weapon.c \
              src/take_screenshot.c \
              src/winclose_handler.c \
              src/main.c
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

all:
	@$(MAKE) fclean
	@git checkout -f master
	@$(MAKE) all
.PHONY: all

linux:
	@$(MAKE) fclean
	@git checkout -f linux
	@$(MAKE) all
.PHONY: linux

bonus: $(NAME)
$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	@echo "$(LGREEN)Linking executable $(NAME)$(NOC)"
	$(CC) $(CFLAGS) $(INCLUDE) ./libsdl2/audio.c $(OBJS) $(LIBS) -o $@
	@echo "Built target $(NAME)"
.PHONY: bonus

$(LIBFT): NONE
	@$(MAKE) -C ./libft
$(LIBMLX): NONE
	@$(MAKE) -C ./libmlx MAKEFLAGS= -j 1
	@cp ./libmlx/libmlx.dylib .
.PHONY: NONE

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -MMD -MF $(DEPDIR)/$*.tmp -c $< -o $@
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
	$(MAKE) bonus
.PHONY: re

help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... bonus"
	@echo "... linux"
	@echo "... clean"
	@echo "... fclean"
	@echo "... re"
.PHONY: help

# Do not include dependency files if the current goal is
# set to clean/fclean/re.
ifeq ($(findstring $(MAKECMDGOALS), clean fclean re),)
    -include $(DEPS)
endif
