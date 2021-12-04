#include "minirt.h"
#include "rt_scene.h"
#include "mr_vec3.h"
#include "mr_utils.h"
#include "mr_camera.h"

#define ASPECT_RATIO (double)16.0 / 9.0
#define HEIGHT 400
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

static bool	rt_hit_object(
	t_element *el,
	const t_ray *ray,
	t_hit_record *rec
)
{
	if (el->etype == RD_ET_SPHERE)
		return (rt_hit_sphere(el, ray, rec));
	if (el->etype == RD_ET_PLANE)
		return (rt_hit_plane(el, ray, rec));
	if (el->etype == RD_ET_CYLINDER)
		return (rt_hit_cylinder(el, ray, rec));
	return (false);
}

static t_vec3	ray_color(t_ray *r, t_scene *scene)
{
	t_vec3			center;
	t_hit_record	rec;

	rec.hit = false;
	mr_vec3_init(&center, 0, 0, 1.2); 		  // 球の中心x
	t_vec3	plain_normal = { 0, -1/sqrt(2), 3/sqrt(2) };
	plain_normal = mr_unit_vector(plain_normal);
	t_element plain;
	plain.position = center;
	plain.direction = plain_normal;
	t_element cylinder;
	cylinder.position = center;
	cylinder.direction = plain_normal;	
	cylinder.diameter = 3/sqrt(2);
	cylinder.height = 5/sqrt(2);
	if (rt_hit_object(scene->objects[0], r, &rec))
	{

		double cos = rec.cos;
		double x = cos * 1; // cos * 輝度
		// t_vec3 base_color = {1, 1, 1};
		t_vec3 base_color = rec.color;
		t_vec3 c = mr_vec3_mul_double(base_color, fabs(x));
		return (c);
	}
	return (sky_blue(r->direction));
}

static void	ray_loop(
	t_camerax *camera,
	t_img *img,
	t_scene *scene)
{
	const double	viewport_z = 0;
	double	i;
	double	j;
	double	u;
	double	v;
	t_vec3	vp_horizontal; // ビューポート幅ベクトル
	t_vec3	vp_vertical; // ビューポート高さベクトル
	t_vec3	vp_lower_left_corner; // ビューポート左下隅
	t_vec3	vp_center; // ビューポート中心
	t_ray	ray;

	vp_center = (t_vec3){ 0, 0, viewport_z };
	vp_vertical = (t_vec3){ 0, 0, 0 };
	vp_vertical.y = camera->vp_height;
	vp_horizontal = (t_vec3){ 0, 0, 0 };
	vp_horizontal.x = camera->vp_width;
	vp_lower_left_corner = vp_center;
	vp_lower_left_corner.y -= camera->vp_height / 2;
	vp_lower_left_corner.x -= camera->vp_width / 2;
	ray.origin = vp_center;
	ray.origin.z -= camera->focal_length;

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
					mr_vec3_mul_double(vp_vertical, v), mr_vec3_mul_double(vp_horizontal, u)
				),
				vp_lower_left_corner
			);
			ray.direction = mr_vec3_sub(ray_cross_screen, ray.origin);
			t_vec3 ray_c = ray_color(&ray, scene);
			t_rgb	rgb = vec3_to_rgb(&ray_c);
			mr_mlx_pixel_put(img, i, j, rgb_to_color(&rgb));
			i += 1;
		}
		j += 1;
	}
}

static void	ray(t_img *img, t_scene *scene)
{
	t_camerax		camera;

	camera.vp_height = 2.0;
	camera.vp_width = ASPECT_RATIO * camera.vp_height;
	camera.focal_length = 1.0;
	ray_loop(&camera, img, scene);
}

int main(int argc, char **argv)
{
	t_info	info;
	t_scene	scene;

	if (argc < 2 || rd_read_scene(argv[1], &scene) == false)
	{
		printf("Error\n");
		return (1);
	}
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "miniRT");
	info.img.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.img.addr = mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.line_len, &info.img.endian);
	ray(&info.img, &scene);
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	mlx_hook(info.win, 17, 1L << 17, &mr_exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}
