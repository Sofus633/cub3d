#include "player.h"
void update_player(t_game *gdata)
{
	t_vector2 old_pos = gdata->player.pos;
	v_add(&gdata->player.pos, gdata->player.vel);
	set_clipping(gdata);
	display_clip(gdata);
	if (is_clipping(gdata->player.clipping))
		gdata->player.pos = old_pos;
	v_mul_scal(&gdata->player.vel, FRICTION);
}

void display_player(t_game *gdata)
{
	dis_rec(gdata->buffer, (t_vector2){gdata->player.pos.x, gdata->player.pos.y}, (t_vector2){CELL_SIZE, CELL_SIZE}, 255);
	if (is_clipping(gdata->player.clipping))
		dis_rec(gdata->buffer, (t_vector2){gdata->player.pos.x, gdata->player.pos.y}, (t_vector2){CELL_SIZE, CELL_SIZE}, -255);
	draw_line(gdata->buffer, (t_vector2){gdata->player.pos.x + CELL_SIZE / 2, gdata->player.pos.y + CELL_SIZE / 2}, (t_vector2){gdata->player.pos.x + CELL_SIZE /2 + (CELL_SIZE * cos(gdata->player.dirrection)),gdata->player.pos.y + CELL_SIZE / 2 + (CELL_SIZE * sin(gdata->player.dirrection))}, 254);	
}
