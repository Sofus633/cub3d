#include "player.h"

t_vector2 direction_vector(double angle, t_vector2 pos)
{
	t_vector2 dir = {cos(angle), sin(angle)};
	float manhattan = fabs(dir.x) + fabs(dir.y);
	t_vector2 out;

	(void)pos;
	out.x = dir.x * (CELL_SIZE / manhattan);
	out.y = dir.y * (CELL_SIZE / manhattan);
	return out;
}

t_vector2 cast_ray(t_vector2 start, float angle, t_game *data)
{
	t_vector2 dvec = direction_vector(angle, start);
	int guard = (WIDTH / CELL_SIZE) * (HEIGHT / CELL_SIZE);

	while (guard-- > 0
		&& start.x >= 0 && start.x < WIDTH
		&& start.y >= 0 && start.y < HEIGHT
		&& !wall_on(start, data))
		start = *v_add(&start, dvec);
	return start;
}

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

void cast_all_rays(t_game *gdata)
{
	t_vector2 center = {gdata->player.pos.x + CELL_SIZE / 2, gdata->player.pos.y + CELL_SIZE / 2};
  float dirrection = gdata->player.dirrection;
  float offset = (FOV / NB_RAY) * (M_PI / 180);
  int i = 0;
	t_vector2 last = (t_vector2){0, 0};
	t_vector2 actual = (t_vector2){0, 0};

  while (i < NB_RAY)
  {
    i++;
		actual = cast_ray(gdata->player.pos, dirrection, gdata);
    draw_line(gdata->buffer, center, actual, 254);
		if (last.x != 0 && last.y != 0)
			draw_line(gdata->buffer, last, actual, 10);
    last = actual;
		dirrection += offset;
  }
}

void display_player(t_game *gdata)
{

	dis_rec(gdata->buffer, (t_vector2){gdata->player.pos.x, gdata->player.pos.y}, (t_vector2){CELL_SIZE, CELL_SIZE}, 255);
	if (is_clipping(gdata->player.clipping))
		dis_rec(gdata->buffer, (t_vector2){gdata->player.pos.x, gdata->player.pos.y}, (t_vector2){CELL_SIZE, CELL_SIZE}, -255);
  cast_all_rays(gdata);
}
