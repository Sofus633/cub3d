CC = cc
EXTERNAL_LIB = -lm
SOURCE = ./source
UTILS = ./utils
SRC = main.c lib/collision/clipping.c \
			lib/graphics/image_manip.c lib/graphics/shapes.c \
			lib/key_handling/key_handling.c \
			lib/object/player.c \
			lib/vector/vector2.c 
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
NAME = cub3d

MLX_DIR = ./lib/mlx_linux
MLX_LIB = $(MLX_DIR)/libmlx.a

CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -g -std=gnu99
LDFLAGS = -L$(MLX_DIR) -L/usr/lib $(EXTERNAL_LIB)

all: compilelib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@echo "$< -> $@  ✨"

compilelib: $(MLX_LIB)
	$(MAKE) -C $(MLX_DIR)
	@printf "🧙 MLX maked\n"

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(MLX_LIB)
	@echo "\n"
	$(CC) $(OBJ) $(LDFLAGS) $(MLX_LIB) -lXext -lX11  -o $(NAME)
	@echo "\n$(OBJ) -> $(NAME) ✨\n"
	@printf "🧙 compilation\033[0;32m SUCESS \033[0m🪄\n"

clean:
	find . -type f \( -name '*.o' -o -name '*.d' \) -delete
	@printf "🧙 allaways at your service to \033[0;32m CLEAN \033[0m🧹\n"

fclean: clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -f $(NAME)
	@printf "🧙 Sending everything to the void \033[0;32m FCLEAN \033[0m🌌\n"

re: fclean all

-include $(DEP)

.PHONY: all compilelib clean fclean re
