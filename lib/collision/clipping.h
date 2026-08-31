#ifndef CLIPPING_H
#define CLIPPING_H
#include "../../cub3d.h"

int wall_on(t_vector2 pos, t_game *data);
void set_clipping(t_game *data);
void display_clip(t_game *data);
int is_clipping(int clip[4]);

#endif // !CLI}}
