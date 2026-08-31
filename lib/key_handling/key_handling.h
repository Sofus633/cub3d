#ifndef KEYHANDLING_H
#define KEYHANDLING_H

# include "../vector/vector2.h" 
# include "../../game.h"
# include "../../cub3d.h"

int	key_press(int key_code, void *param);
int	key_rel(int key_code, void *param);
void event_on_keys(t_game *data);

#endif
