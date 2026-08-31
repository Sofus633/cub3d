#include "clipping.h"

int wall_on(t_vector2 pos, t_game *data)
{
	if (data->map[(int)(pos.y/CELL_SIZE)][(int)(pos.x/CELL_SIZE)])
		return 1;
	return 0;
}

void set_clipping(t_game *data)
{
	t_player player = data->player;
	data->player.clipping[0] = wall_on(player.pos, data);
	data->player.clipping[1] = wall_on(*v_add(&player.pos, (t_vector2){CELL_SIZE, 0}), data);
	data->player.clipping[2] = wall_on(*v_add(&player.pos, (t_vector2){0, CELL_SIZE}), data);
	data->player.clipping[3] = wall_on(*v_add(&player.pos, (t_vector2){CELL_SIZE, CELL_SIZE}), data);
	display_clip(data);
}

void display_clip(t_game *data)
{
	printf("%d %d %d %d\n", data->player.clipping[0], data->player.clipping[1], data->player.clipping[2], data->player.clipping[3]);
}

int is_clipping(int clip[4])
{
	return (clip[0] || clip[1] || clip[2] || clip[3]);
}
