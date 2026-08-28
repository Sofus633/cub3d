CC = cc
EXTERNAL_LIB = -lm
SOURCE = ./source
UTILS = ./utils
SRC = main.c
OBJ = $(SRC:.c=.o)
NAME = cub3d

MLX_DIR = ./mlx_linux

CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -g -std=gnu99
LDFLAGS = -L$(MLX_DIR) -L/usr/lib $(EXTERNAL_LIB)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$< -> $@  ✨"

compilelib:
	@make -C $(MLX_DIR)
	@printf "🧙 MLX maked\n"

$(NAME): $(OBJ)
	@make compilelib
	@echo "\n"
	$(CC) $(OBJ) $(LDFLAGS) $(MLX_DIR)/libmlx.a -lXext -lX11  -o $(NAME)
	@echo "\n$(OBJ) -> $(NAME) ✨\n"
	@printf "🧙 compilation\033[0;32m SUCESS \033[0m🪄\n"

clean:
	find . -type f -name *.o -delete
	@printf "🧙 allaways at your service to \033[0;32m CLEAN \033[0m🧹\n"

fclean: clean
	rm -f $(NAME)
	@printf "🧙 Sending everything to the void \033[0;32m FCLEAN \033[0m🌌\n"

re: fclean all
