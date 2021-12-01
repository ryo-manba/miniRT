#include "minirt.h"
#include "rt_scene.h"
#include "mr_vec3.h"
#include "mr_utils.h"

#define ASPECT_RATIO (double)16.0 / 9.0
#define HEIGHT 250
#define WIDTH HEIGHT * ASPECT_RATIO
#define EPS 1e-9


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
	return (rt_create_trgb(0, rgb->r, rgb->g, rgb->b));
}

// 光源の強さ * cosθ
int	rt_lamberdian(t_vec3 *light)
{
	(void)light;	
	return (0);
}

static t_vec3	ray_color(t_ray *r)
{
	t_vec3	unit_direction = mr_unit_vector(r->direction);
	t_vec3			center;
	t_vec3			c1; // 白
	t_vec3			c2; // 青
	double			t;
	t_hit_record	rec;


//	mr_vec3_init(&center, 0, 0, -1.0);

//	t_vec3 point;
//	mr_vec3_init(&point, -0.6, 0, -1.0);
//
//	t_vec3 point2;
//	mr_vec3_init(&point2, 0.0, 100, -1.0);


	mr_vec3_init(&center, 0, 0, -1.0);
	if (rt_hit_sphere(&center, 0.5, r, &rec)) // 球とヒットした場合
	{
		// 法線ベクトルを求める
		t_vec3 tmp1 = mr_vec3_sub(rec.p, center);
		tmp1 = mr_unit_vector(tmp1);

		// cosθを求める
		t_vec3 tmp2 = rec.normal;
		double cos = mr_vec3_dot(tmp1, tmp2);

		double x = cos * 0.1; // cos * 輝度
		return (mr_vec3_mul_double(rec.p, x));
	}
	// else if (rt_hit_sphere(&point, 0.5, r, &rec))
	// {
	// 	t_vec3	target = mr_vec3_add(mr_vec3_add(rec.p, rec.normal), rt_random_unit_vector());
	// 	t_ray	ray;
	// 	ray.origin = rec.p;
	// 	ray.direction = mr_vec3_sub(target, rec.p);
	// 	return (mr_vec3_mul_double(ray_color(&ray, depth - 1), 0.3 + EPS));

	// } 
	// else if (rt_hit_sphere(&point2, 99, r, &rec))
	// {
	// 	t_vec3	target = mr_vec3_add(mr_vec3_add(rec.p, rec.normal), rt_random_unit_vector());
	// 	t_ray	ray;
	// 	ray.origin = rec.p;
	// 	ray.direction = mr_vec3_sub(target, rec.p);
	// 	return (mr_vec3_mul_double(ray_color(&ray, depth - 1), 0.9 + EPS));
	// }

	unit_direction = mr_unit_vector(r->direction);
	t = 0.5  * (unit_direction.y + 1.0);
	mr_vec3_init(&c1, 1.0, 1.0, 1.0);
	mr_vec3_init(&c2, 0.5, 0.7, 1.0);
	c1 = mr_vec3_mul_double(c1, t);
	c2 = mr_vec3_mul_double(c2, 1 - t);

	return (mr_vec3_add(c1, c2));
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
			u = i / (WIDTH-1);  // [0,1]
			v = j / (HEIGHT-1); // [0,1]
			// rayの方向ベクトル = (viewportの左下 + (水平方向ベクトル * u)) + (垂直方向ベクトル * v)) - rayの原点)
			ray->direction = mr_vec3_sub(
							mr_vec3_add(mr_vec3_add(*lower_left_corner, mr_vec3_mul_double(*horizontal, u)),
							mr_vec3_mul_double(*vertical, v)),
							ray->origin);

			t_vec3 ray_c = ray_color(ray);

			t_rgb	rgb = vec3_to_rgb(&ray_c);
			mr_mlx_pixel_put(img, i, j, rgb_to_color(&rgb));
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

	mr_vec3_init(&ray.origin, 0, 0, 0);
	mr_vec3_init(&horizontal, viewport_width, 0, 0);
	mr_vec3_init(&vertical, 0, viewport_height, 0);
	lower_left_corner = mr_vec3_sub(mr_vec3_sub(ray.origin, mr_vec3_div_double(horizontal, 2.0)),
					 	mr_vec3_div_double(vertical, 2.0));
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
	mlx_hook(info.win, 17, 1L << 17, &mr_exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}
