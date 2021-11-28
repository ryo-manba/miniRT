#include "minirt.h"

void	plot(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			my_mlx_pixel_put(img, i, j, color);
			j += 1;
		}
		i += 1;
	}
}

#define T 0
#define R 0
#define G 255
#define B 255

int main()
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		color;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	color = create_trgb(T, R, G, B);
	color = add_shade(0.25f, color);
//	color = get_opposite(color);
	plot(&img, color);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
//	mlx_hook(info.win, 17, 1L << 17, &exit_window, &info);
	return (0);
}
