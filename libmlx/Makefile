MODULE_SRC := mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ := $(MODULE_SRC:%.swift=%.swiftmodule)
SRC        := interface.swift $(MODULE_SRC)
OBJ        :=$(SRC:%.swift=%.o)
C_SRC      := mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ      :=$(C_SRC:%.c=%.o)
CFLAGS     := -O2

NAME       := libmlx.dylib
INC        := -I.
#OPTI      := -Ounchecked

# Define some colors for echo:
LGREEN     := \033[1;32m
WHITE      := \033[1;37m
NOC        := \033[0m

all: $(NAME)
$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	@echo "$(LGREEN)Linking Swift dynamic library $(NAME)$(NOC)"
	@swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz
	@echo "Built target $(NAME)"

%.swiftmodule: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)
	@touch $@

%.o: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@
	@touch $@

clean:
	rm -f $(NAME) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~
.PHONY: clean
