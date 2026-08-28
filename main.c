#include "./mlx_linux/mlx.h"
#include <stdlib.h>

#define HEIGHT 800
#define WIDTH 800
#define CELL_SIZE 10


typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector2;

typedef struct t_player
{
	t_vector2 pos;
} t_player;


typedef struct s_image
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}t_image;

typedef struct t_game
{
	void *mlx;
	void *win;
	t_image *buffer;
	t_player player;
}t_game ;


t_image	*t_new_image(void *mlx, int x, int y)
{
	t_image	*nimg;

	nimg = malloc(sizeof(t_image));
	if (!nimg)
		return (NULL);
	nimg->img = mlx_new_image(mlx, x, y);
	nimg->height = x;
	nimg->width = y;
	nimg->data = mlx_get_data_addr(nimg->img, &nimg->bpp,
			&nimg->size_line, &nimg->endian);
	return (nimg);
}

void	my_mlx_pixel_put(t_image *t_image, int x, int y, int color)
{
	char	*dst;

	dst = t_image->data + (y * t_image->size_line + x * (t_image->bpp / 8));
	*(unsigned int *)dst = color;
}

char	*my_mlx_pixel_get(t_image *t_image, int x, int y)
{
	char	*dst;

	dst = t_image->data + (y * t_image->size_line + x * (t_image->bpp / 8));
	return (dst);
}

void	dis_rec(t_image *img, t_vector2 pos, t_vector2 size, int color)
{
	int	x;
	int	y;
	int	ox;

	x = pos.x;
	y = pos.y;
	ox = x;
	while (y < pos.y + size.y)
	{
		while (x < pos.x + size.x)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		x = ox;
		y++;
	}
}


int loop(t_game *gdata)
{
	for (int y = 0; y < HEIGHT; y += CELL_SIZE)
	{
		for (int x = 0; x < WIDTH; x += CELL_SIZE)
		{
			dis_rec(gdata->buffer, (t_vector2){x, y}, (t_vector2){CELL_SIZE - 1, CELL_SIZE - 1}, 125);
		}
	}

	dis_rec(gdata->buffer, (t_vector2){gdata->player.pos.x, gdata->player.pos.y}, (t_vector2){CELL_SIZE, CELL_SIZE}, 255);

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
	gdata.player = (t_player){(t_vector2){10 ,10}};
	
	mlx_loop_hook(mlx, loop, &gdata);
	mlx_loop(mlx);
	(void)win;
}
