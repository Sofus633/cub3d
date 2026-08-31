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
	return (1);
}

void event_on_keys(t_game *data)
{
	if (data->key_release[D] == 1)
		data->player.dirrection += TURN_FORCE;
	if (data->key_release[A] == 1)
		data->player.dirrection -= TURN_FORCE;
	if (data->key_release[W] == 1)
	{
		data->player.vel.x += cos(data->player.dirrection) * SPEED;
		data->player.vel.y += sin(data->player.dirrection) * SPEED;
	}
}
