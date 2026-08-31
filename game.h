#ifndef GAME_STRUCT
#define GAME_STRUCT

# include "lib/graphics/graphic.h"

typedef struct t_player
{
	t_vector2 pos;
	t_vector2 vel;
	float dirrection;
	int clipping[4];
} t_player;

typedef struct t_game
{
	void *mlx;
	void *win;
	t_image *buffer;
	t_player player;
	int **map;
	int			key_release[256];
}t_game ;

#endif // !GAME_STRUCT
