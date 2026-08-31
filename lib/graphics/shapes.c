#include "graphic.h"

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
