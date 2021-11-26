#include "minirt.h"

static bool	rt_is_valid_file(char *filename)
{
	return (true);
}

static void	rt_plot(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		while (j < WIDTH)
		{
//			my_mlx_pixel_put();
			j += 1;
		}
		i += 1;
	}
}

int main(int argc, char **argv)
{
	void	*mlx;

//	plot();
	mlx = mlx_init();
	mlx_put_image_to_window(mlx, HEIGHT, WIDTH, "miniRT");
//	mlx_hook(info.win, 17, 1L << 17, &exit_window, &info);
	return (0);
}
