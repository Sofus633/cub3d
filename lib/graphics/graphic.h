#ifndef GRAPHIC_H
#define GRAPHIC_H

# include <math.h> 
# include "../vector/vector2.h"
# include "../mlx_linux/mlx.h"
# include <stdlib.h>
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

t_image	*t_new_image(void *mlx, int x, int y);
void	my_mlx_pixel_put(t_image *t_image, int x, int y, int color);
char	*my_mlx_pixel_get(t_image *t_image, int x, int y);
void	clean_buffer(t_image *img, int color);

void	draw_line(t_image *img, t_vector2 vec1, t_vector2 vec2, int color);
void	dis_rec(t_image *img, t_vector2 pos, t_vector2 size, int color);

#endif // !GRAPHIC_H
