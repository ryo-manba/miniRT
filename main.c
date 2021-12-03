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

static t_vec3	sky_blue(t_vec3 direction)
{
	const t_vec3 c1 = {1.0, 1.0, 1.0}; // 白
	const t_vec3 c2 = {0.5, 0.7, 1.0}; // 青
	const t_vec3 unit_direction = mr_unit_vector(direction);
	const double t = 0.5  * (unit_direction.y + 1.0);

	return (mr_vec3_add(
			mr_vec3_mul_double(c1, t),
			mr_vec3_mul_double(c2, 1 - t)));
}

static t_vec3	ray_color(t_ray *r)
{
	t_vec3			center;
	t_hit_record	rec;

	rec.hit = false;
	mr_vec3_init(&center, 0, 0, 1.5 - 1.5); 		  // 球の中心x
	t_vec3	plain_normal = { 0, -1/sqrt(2), 1/sqrt(2) };
	plain_normal = mr_unit_vector(plain_normal);
	t_element plain;
	plain.position = center;
	plain.direction = plain_normal;
	t_element cylinder;
	cylinder.position = center;
	cylinder.direction = plain_normal;	
	cylinder.diameter = 1/sqrt(2);
	cylinder.height = 5/sqrt(2);
	// if (rt_hit_sphere(&center, 4.5, r, &rec)) // 球とヒットした場合
	// if (rt_hit_plain(&plain, r, &rec)) // 平面とヒットした場合
	if (rt_hit_cylinder(&cylinder, r, &rec)) // 円柱とヒットした場合
	{
		// 法線ベクトルを求める
		t_vec3 tmp1 = rec.p;
//		t_vec3 tmp1 = mr_vec3_sub(r->direction, center);
		tmp1 = mr_unit_vector(tmp1);

//		vec3_debug(&t);
//		vec3_debug(&rec.p);
		
//		vec3_debug(&tmp1);
//		vec3_debug(&tmp1);
//		exit(1);
		// cosθを求める
//		t_vec3 tmp1 = mr_vec3_sub(rec.p, center);
		t_vec3 tmp2 = mr_unit_vector(rec.normal);
		
		double cos = mr_vec3_dot(tmp1, tmp2);
		double x = cos * 0.5; // cos * 輝度
		t_vec3 base_color = { 1, 1, 1 };
		t_vec3 c = mr_vec3_mul_double(base_color, x);
		c.x = fabs(c.x);
		c.y = fabs(c.y);
		c.z = fabs(c.z);
		return (c);
	}
	return (sky_blue(r->direction));
}

static void	ray_loop(t_ray *ray, t_vec3 *vp_lower_left_corner, t_vec3 *horizontal, t_vec3 *vertical, t_img *img)
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
			u = i / (WIDTH);  // [0,1]
			v = j / (HEIGHT); // [0,1]
			// rayの方向ベクトル = (viewportの左下 + (水平方向ベクトル * u)) + (垂直方向ベクトル * v)) - rayの原点)

			t_vec3 ray_cross_screen = mr_vec3_add(
				mr_vec3_add(
					mr_vec3_mul_double(*vertical, v), mr_vec3_mul_double(*horizontal, u)
				),
				*vp_lower_left_corner
			);
			ray->direction = mr_vec3_sub(
								ray_cross_screen, ray->origin
							);
			// vec3_debug(&ray->direction);
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
	const double 	viewport_z = 0;
	const double 	focal_length = 1.0;
	t_vec3			horizontal; // ビューポート幅ベクトル
	t_vec3			vertical; // ビューポート高さベクトル
	t_vec3			vp_lower_left_corner; // ビューポート左下隅
	t_vec3			vp_center; // ビューポート中心
	t_vec3			coordinate_origin; // 座標原点
	t_ray			ray;

	mr_vec3_init(&coordinate_origin, 0, 0, 0);
	vp_center = coordinate_origin;
	vp_center.z = viewport_z;
	ray.origin = vp_center;
	ray.origin.z -= focal_length;
	mr_vec3_init(&horizontal, viewport_width, 0, viewport_z);
	mr_vec3_init(&vertical, 0, viewport_height, viewport_z);
	vp_lower_left_corner = mr_vec3_sub(
		mr_vec3_sub(
			vp_center, mr_vec3_div_double(horizontal, 2)
		),
		mr_vec3_div_double(vertical, 2)
	);
	// vp_lower_left_corner.z -= focal_length;
	ray_loop(&ray, &vp_lower_left_corner, &horizontal, &vertical, img);
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
