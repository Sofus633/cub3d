#ifndef PLAYER_H
#define PLAYER_H

# include "../../game.h"
# include "../collision/clipping.h"

void update_player(t_game *gdata);
void display_player(t_game *gdata);
t_vector2 direction_vector(double angle, t_vector2 pos);
t_vector2 cast_ray(t_vector2 start, float angle, t_game *data);

#endif
