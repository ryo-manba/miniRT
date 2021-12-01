#include "minirt.h"

#define T 0
#define R 255
#define G 0
#define B 0
#define RAD 100
#define CENTER_X HEIGHT / 2
#define CENTER_Y WIDTH / 2

#define EDGE 100
#define HALF_EDGE EDGE / 2


bool	is_in_square(int x, int y)
{
	return ((abs(CENTER_X - x) <= HALF_EDGE) && (abs(CENTER_Y - y) <= HALF_EDGE));
}

bool	is_in_circle(int x, int y)
{
	return ((pow((x - CENTER_X), 2) + pow((y - CENTER_Y), 2) <= pow(RAD, 2)));
}

bool	is_in_triangle(int x, int y)
{
	if (y >= CENTER_Y)
		return (false);
	return ((2 * (abs(CENTER_X - x)) + (abs(CENTER_Y - y)) <= EDGE));
}

// 横長になる
bool	is_in_hexagon(int x, int y)
{
	const int check = ((2 * (abs(CENTER_Y - y)))
	+ fabs((sqrt(3) * (CENTER_X - x)) - (sqrt(3) * (CENTER_Y - y)))
	+ fabs((sqrt(3) * ((CENTER_X - x))) + (sqrt(3) * (CENTER_Y - y))));

	return (check <= 2 * EDGE * sqrt(3));
}

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
			if (is_in_circle(i, j))
			{
				mr_mlx_pixel_put(img, i, j, color);
			}
			else
			{
				mr_mlx_pixel_put(img, i, j, rt_get_opposite(color));
			}
			j += 1;
		}
		i += 1;
	}
}

static int	mr_exit_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

int main()
{
	t_info	info;
	int		color;

	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "miniRT");
	info.img.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.img.addr = mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.line_len, &info.img.endian);
	color = rt_create_trgb(T, R, G, B);
	plot(&info.img, color);
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	mlx_hook(info.win, 17, 1L << 17, &mr_exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}
