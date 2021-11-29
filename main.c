#include "minirt.h"
#include "rt_scene.h"
#include "mr_vec3.h"

#define ASPECT_RATIO (double)16.0 / 9.0
#define HEIGHT 250
#define WIDTH HEIGHT * ASPECT_RATIO

static int	exit_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

static t_rgb vec3_to_rgb(t_vec3 *vec3)
{
	t_rgb	rgb;

	rgb.r = vec3->x * 255.999;
	rgb.g = vec3->y * 255.999;
	rgb.b = vec3->z * 255.999;
	return (rgb);
}

static int	rgb_to_color(t_rgb *rgb)
{
	return (create_trgb(0, rgb->r, rgb->g, rgb->b));
}

static void vec3_init(t_vec3 *vec3, double x, double y, double z)
{
	vec3->x = x;
	vec3->y = y;
	vec3->z = z;
}

static t_vec3	ray_color(t_ray *r)
{
	const t_vec3	unit_direction = unit_vector(r->direction);
	t_vec3			point3;
	t_vec3			c1; // 白
	t_vec3			c2; // 青
	double			t;

	vec3_init(&point3, 0, 0, -1.0);
	t =  rt_hit_sphere(&point3, 0.5, r); // 球とヒットした場合
	if (t > 0.0)
	{
		vec3_init(&point3, 1, 0, 0);
		return (point3); // rgbの割合を返す
	}
	t = 0.5  * (unit_direction.y + 1.0);
	vec3_init(&c1, 1.0, 1.0, 1.0);
	vec3_init(&c2, 0.5, 0.7, 1.0);
	c1 = vec3_mul_double(c1, t);
	c2 = vec3_mul_double(c2, 1 - t);
	return (vec3_add(c1, c2));
}

static void	ray_loop(t_ray *ray, t_vec3 *lower_left_corner, t_vec3 *horizontal, t_vec3 *vertical, t_img *img)
{
	double	i;
	double	j;
	double	u;
	double	v;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			u = i / (WIDTH-1);
			v = j / (HEIGHT-1);
			ray->direction = vec3_sub(vec3_add(vec3_add(*lower_left_corner, vec3_mul_double(*horizontal, u)),
												vec3_mul_double(*vertical, v)), ray->origin);
			t_vec3	ray_c = ray_color(ray);
			t_rgb	rgb = vec3_to_rgb(&ray_c);
			my_mlx_pixel_put(img, i, j, rgb_to_color(&rgb));
			i += 1;
		}
		j += 1;
	}
}

static void	ray(t_img *img)
{
	const double 	viewport_height = 2.0;
	const double 	viewport_width = ASPECT_RATIO * viewport_height;
	const double 	focal_length = 1.0;
	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			lower_left_corner;
	t_ray			ray;

	vec3_init(&ray.origin, 0, 0, 0);
	vec3_init(&horizontal, viewport_width, 0, 0);
	vec3_init(&vertical, 0, viewport_height, 0);
	lower_left_corner = vec3_sub(vec3_sub(ray.origin, vec3_div_double(horizontal, 2.0)),
					 	vec3_div_double(vertical, 2.0));
	lower_left_corner.z -= focal_length;
	ray_loop(&ray, &lower_left_corner, &horizontal, &vertical, img);
}

int main()
{
	t_info	info;

	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "miniRT");
	info.img.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.img.addr = mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.line_len, &info.img.endian);
	ray(&info.img);
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	mlx_hook(info.win, 17, 1L << 17, &exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}
