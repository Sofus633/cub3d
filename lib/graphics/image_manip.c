#include "graphic.h"

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
