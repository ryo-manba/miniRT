#include "minirt.h"

int main()
{
	void	*mlx;
	void	*win;
	t_img	img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	my_mlx_pixel_put(&img, WIDTH / 2, HEIGHT / 2, 0xFF0000);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
//	mlx_hook(info.win, 17, 1L << 17, &exit_window, &info);
	return (0);
}
