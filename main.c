#include "minirt.h"
#include "rt_scene.h"
#include "vec3.h"

void plot(t_img *img)
{
	t_rgb	rgb;
	const int image_width = WIDTH;
	const int image_height = HEIGHT;

	for (double j = 0; j <= image_height; ++j) {
		for (double i = 0; i < image_width; ++i) {
			rgb.r = (255.999 * (i / (image_width-1)));
			rgb.g = (255.999 * (j / (image_height-1)));
			rgb.b = (255.999 * 0.25);
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

static void vec3_init(t_vec3 *vec3)
{
	vec3->x = 0;
	vec3->y = 0;
	vec3->z = 0;
}

//  return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
static t_vec3	ray_color(t_ray *r)
{
	t_vec3 unit_direction = unit_vector(r->direction);
	double t = 0.5  *(unit_direction.y + 1.0);

	t_vec3	c1; // 白
	c1.x = 1.0;
	c1.y = 1.0;
	c1.z = 1.0;

	t_vec3 c2; // 青
	c2.x = 0.5;
	c2.y = 0.7;
	c2.z = 1.0;

	c1 = vec3_mul_double(c1, t);
	c2 = vec3_mul_double(c2, 1 - t);
	return (vec3_add(c1, c2));
}

static void	ray(t_img *img)
{
	const double	aspect_ratio = 16.0 / 9.0;
//	const int		image_width = 384;
	const int		image_width = WIDTH;
//	const int		image_height = image_width / aspect_ratio;
	const int		image_height = HEIGHT;
	double 			viewport_height = 2.0;
	double 			viewport_width = aspect_ratio * viewport_height;
	double 			focal_length = 1.0;
	t_vec3			origin;
	t_vec3			horizontal;
	t_vec3			vertical;

	vec3_init(&origin);
	vec3_init(&horizontal);
	horizontal.x = viewport_width;
	vec3_init(&vertical);
	vertical.y = viewport_height;

	t_vec3	lower_left_corner;
	vec3_init(&lower_left_corner);

	lower_left_corner = vec3_sub(origin, vec3_div_double(horizontal, 2.0));
	lower_left_corner = vec3_sub(lower_left_corner, vec3_div_double(vertical, 2.0));
	lower_left_corner.z -= focal_length;

//	printf("%f, %f, %f\n", lower_left_corner.x, lower_left_corner.y, lower_left_corner.z);
	for (double j = image_height-1; j >= 0; --j) {
		for (double i = 0; i < image_width; ++i) {

			double u = i / (image_width-1);
			double v = j / (image_height-1);

			t_ray r;
			r.origin = origin;

			t_vec3 ho = vec3_mul_double(horizontal, u);
			r.direction = vec3_add(lower_left_corner, ho);
			t_vec3 ve = vec3_mul_double(vertical, v);
			r.direction = vec3_add(r.direction, ve);
			r.direction = vec3_sub(r.direction, origin);

			t_vec3 ray_c = ray_color(&r);

			t_rgb rgb;
			rgb.r = ray_c.x * 255.999;
			rgb.g = ray_c.y * 255.999;
			rgb.b = ray_c.z * 255.999;

			int color = create_trgb(0, rgb.r, rgb.g, rgb.b);
			my_mlx_pixel_put(img, i, j, color);
		}
	}

}

int main()
{
	t_info	info;

	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "miniRT");
	info.img.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.img.addr = mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.line_len, &info.img.endian);
//	plot(&info.img);
	ray(&info.img);
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	mlx_hook(info.win, 17, 1L << 17, &exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}
