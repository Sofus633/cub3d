#include "cub3d.h"

int loop(t_game *gdata)
{
	clean_buffer(gdata->buffer, 0);
	
	//display grid
	for (int y = 0; y < HEIGHT; y += CELL_SIZE)
	{
		for (int x = 0; x < WIDTH; x += CELL_SIZE)
		{ 
			if (gdata->map[y/CELL_SIZE][x/CELL_SIZE] == 0)
				dis_rec(gdata->buffer, (t_vector2){x, y}, (t_vector2){CELL_SIZE - 1, CELL_SIZE - 1}, 125);
			else 
				dis_rec(gdata->buffer, (t_vector2){x, y}, (t_vector2){CELL_SIZE - 1, CELL_SIZE - 1}, 1000);
		}
	}

	event_on_keys(gdata);

	update_player(gdata);
	display_player(gdata);

	mlx_put_image_to_window(gdata->mlx, gdata->win,
		gdata->buffer->img, 0, 0);
	
	return 1;
}

int main(void){
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, 800, 800, "Cub3d");
	t_game gdata;

	gdata.mlx = mlx;
	gdata.win = win;
	gdata.buffer = t_new_image(mlx, 800, 800);
	gdata.player = (t_player){(t_vector2){100 ,100}, (t_vector2){0, 0}, 0., {0, 0, 0, 0}};
	gdata.map = malloc((HEIGHT / CELL_SIZE) * sizeof(int *));
	for (int y = 0 ; y < HEIGHT / CELL_SIZE; y++)
	{
		gdata.map[y] = malloc((WIDTH / CELL_SIZE) * sizeof(int));
		for (int x = 0; x < WIDTH / CELL_SIZE; x++){
			gdata.map[y][x] = 0;
			if (y == 0 || y == (HEIGHT / CELL_SIZE) - 1 || x == 0 || x == (WIDTH / CELL_SIZE) - 1 ||
				(y == 5 && (x < 10 || x > 30))  ||
				(y == 30 && (x < 40 || x > 500))||
				(y == 40 && (x < 30 || x > 60)) ||
				(y == 60 && (x < 5 || x > 20))  ||
				(y == 20 && (x < 0 || x > 30))
			)
				gdata.map[y][x] = 1;
		}
	}
	mlx_hook(win, 2, 1L << 1, key_press, &gdata);
	mlx_hook(win, 3, 1L << 0, key_rel, &gdata);
	mlx_loop_hook(mlx, loop, &gdata);
	mlx_loop(mlx);
	(void)win;
}
