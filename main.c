#include "minirt.h"
#include "vec3.h"

void plot(t_img *img)
{
	t_rgb	rgb;
	const int image_width = WIDTH;
	const int image_height = HEIGHT;

//	for (double j = image_height-1; j >= 0; --j) {
	for (double j = 0; j <= image_height; ++j) {
//		fprintf(stderr, "Scanlines remining: %d", (int)j);
//		fflush(stderr);
		for (double i = 0; i < image_width; ++i) {
			rgb.r = (255.99 * i / (image_width-1));
			rgb.g = (255.99 * i / (image_height-1));
			rgb.b = (255.99 * 0.25);
			int color = create_trgb(0, rgb.r, rgb.g, rgb.b);
			my_mlx_pixel_put(img, i, j, color);
		}
	}
}

static int	exit_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

int main()
{
	t_info	info;

	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "miniRT");
	info.img.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.img.addr = mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.line_len, &info.img.endian);
	plot(&info.img);
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	mlx_hook(info.win, 17, 1L << 17, &exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}
