#include "key_handling.h"

int	key_press(int key_code, void *param)
{
	t_game	*p;

	p = (t_game *)param;
	if (key_code == W)
		p->key_release[W] = 1;
	if (key_code == S)
		p->key_release[S] = 1;
	if (key_code == A)
		p->key_release[A] = 1;
	if (key_code == D)
		p->key_release[D] = 1;
	if (key_code == SPACE)
		p->key_release[SPACE] = 1;
	if (key_code == ARROW_UP)
		p->key_release[ARROW_UP] = 1;
	if (key_code == ARROW_DOWN)
		p->key_release[ARROW_DOWN] = 1;
	if (key_code == ARROW_LEFT)
		p->key_release[ARROW_LEFT] = 1;
	if (key_code == ARROW_RIGHT)
		p->key_release[ARROW_RIGHT] = 1;
	return (1);
}

int	key_rel(int key_code, void *param)
{
	t_game	*p;

	p = (t_game *)param;
	if (key_code == W)
		p->key_release[W] = 0;
	if (key_code == S)
		p->key_release[S] = 0;
	if (key_code == A)
		p->key_release[A] = 0;
	if (key_code == D)
		p->key_release[D] = 0;
	if (key_code == ARROW_UP)
		p->key_release[ARROW_UP] = 0;
	if (key_code == ARROW_DOWN)
		p->key_release[ARROW_DOWN] = 0;
	if (key_code == ARROW_LEFT)
		p->key_release[ARROW_LEFT] = 0;
	if (key_code == ARROW_RIGHT)
		p->key_release[ARROW_RIGHT] = 0;
	return (1);
}

void event_on_keys(t_game *data)
{
	if (data->key_release[D] == 1)
		data->player.vel.x += SPEED;
	//data->player.dirrection += TURN_FORCE;
	if (data->key_release[A] == 1)
		data->player.vel.x -= SPEED;
	if (data->key_release[S] == 1)
		data->player.vel.y += SPEED;
	if (data->key_release[W] == 1)
		data->player.vel.y -= SPEED;
  if (data->key_release[ARROW_RIGHT])
    data->player.dirrection += TURN_FORCE;
  if (data->key_release[ARROW_LEFT])
    data->player.dirrection -= TURN_FORCE;
}
