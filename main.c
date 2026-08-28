#include "./mlx_linux/mlx.h"
#include <stdlib.h>
#include <math.h>

#define HEIGHT 800
#define WIDTH 800
#define CELL_SIZE 10
#define D 'd'
#define A 'a'
#define S 's'
#define W 'w'
#define SPACE ' '
#define TURN_FORCE .01

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector2;

typedef struct t_player
{
	t_vector2 pos;
	float dirrection;
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
	int			key_release[256];
}t_game ;

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

void	clean_buffer(t_image *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
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


void	draw_line(t_image *img, t_vector2 vec1, t_vector2 vec2, int color)
{
	t_vector2	delta;
	t_vector2	cur;
	int			steps;
	int			i;

	delta.x = vec2.x - vec1.x;
	delta.y = vec2.y - vec1.y;
	steps = fmax(fabs(delta.x), fabs(delta.y));
	if (steps == 0)
		steps = 1;
	delta.x /= steps;
	delta.y /= steps;
	cur = vec1;
	i = 0;
	while (i <= steps)
	{
		if (cur.x >= 0 && cur.x < img->width && cur.y >= 0 && cur.y < img->height)
			my_mlx_pixel_put(img, cur.x, cur.y, color);
		cur.x += delta.x;
		cur.y += delta.y;
		i++;
	}
}

int loop(t_game *gdata)
{
	clean_buffer(gdata->buffer, 0);
	for (int y = 0; y < HEIGHT; y += CELL_SIZE)
	{
		for (int x = 0; x < WIDTH; x += CELL_SIZE)
		{
			dis_rec(gdata->buffer, (t_vector2){x, y}, (t_vector2){CELL_SIZE - 1, CELL_SIZE - 1}, 125);
		}
	}

	if (gdata->key_release[D] == 1)
		gdata->player.dirrection += TURN_FORCE;
	if (gdata->key_release[A] == 1)
		gdata->player.dirrection -= TURN_FORCE;
	if (gdata->key_release[W] == 1)
	{
		gdata->player.pos.x += cos(gdata->player.dirrection);
		gdata->player.pos.y += sin(gdata->player.dirrection);
	}
	dis_rec(gdata->buffer, (t_vector2){gdata->player.pos.x, gdata->player.pos.y}, (t_vector2){CELL_SIZE, CELL_SIZE}, 255);
	draw_line(gdata->buffer, (t_vector2){gdata->player.pos.x + CELL_SIZE / 2, gdata->player.pos.y + CELL_SIZE / 2}, (t_vector2){gdata->player.pos.x + CELL_SIZE /2 + (CELL_SIZE * cos(gdata->player.dirrection)),gdata->player.pos.y + CELL_SIZE / 2 + (CELL_SIZE * sin(gdata->player.dirrection))}, 254);
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
	gdata.player = (t_player){(t_vector2){10 ,10}, 0.};
	gdata.map = malloc((HEIGHT / CELL_SIZE) * sizeof(int *));
	for (int y = 0 ; y < HEIGHT; y += CELL_SIZE)
	{
		for (int x = 0; x < WIDTH; x += CELL_SIZE){
			gdata.map[y] = malloc((WIDTH))
		}
	}
	mlx_hook(win, 2, 1L << 1, key_press, &gdata);
	mlx_hook(win, 3, 1L << 0, key_rel, &gdata);
	mlx_loop_hook(mlx, loop, &gdata);
	mlx_loop(mlx);
	(void)win;
}
