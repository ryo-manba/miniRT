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

static double	azimuth_yup(t_vec3 *vec)
{
	const double	phi = atan2(vec->x, vec->z);
	printf("(x,z) = (%f,%f), phi = %f\n", vec->x, vec->z, phi);
	if (vec->z >= 0)
		return (phi);
	return (phi);
}

static double	elevation_yup(t_vec3 *vec)
{
	const double	x = sqrt(vec->x * vec->x + vec->z * vec->z);
	const double	theta = atan2(vec->y, x);
	return (theta);
}

static t_vec3	rot_around_axis(t_vec3 *r, t_vec3 *n, double angle)
{
	return mr_vec3_add(
		mr_vec3_add(
			mr_vec3_mul_double(*r, cos(angle)),
			mr_vec3_mul_double(
				*n,
				mr_vec3_dot(*n, *r) * (1 - cos(angle))
			)
		),
		mr_vec3_mul_double(
			mr_vec3_cross(*n, *r),
			sin(angle)
		)
	);
}

static t_vec3	orient_vector(t_vec3 *v, t_vec3 *orient)
{
	t_vec3 az_axis = {0, 1, 0};
	t_vec3 el_axis = {-1, 0, 0};
	double az = azimuth_yup(orient);
	double el = elevation_yup(orient);
	printf("orient: ");
	vec3_debug(orient);
	printf("az = %f, el = %f\n", az, el);
	t_vec3 v2 = rot_around_axis(v, &az_axis, az);
	t_vec3 el_axis2 = rot_around_axis(&el_axis, &az_axis, az);
	return rot_around_axis(&v2, &el_axis2, el);
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

static t_vec3	ray_color(t_ray *r, t_scene *scene, t_hit_record *recs)
{
	t_hit_record	*actual;
	size_t			i;

	actual = NULL;
	i = 0;
	while (i < scene->n_objects)
	{
		if (rt_hit_object(scene->objects[i], r, &recs[i]))
		{
			if (!actual || recs[i].t < actual->t)
				actual = &recs[i];
		}
		i += 1;
	}
	if (actual)
	{
		double cos = actual->cos;
		double x = cos * 1; // cos * 輝度
		t_vec3 base_color = actual->color;
		t_vec3 c = mr_vec3_mul_double(base_color, fabs(x));
		return (c);
	}
	return (sky_blue(r->direction));
}

static void	ray_loop(
	t_viewport *camera,
	t_img *img,
	t_scene *scene)
{
	double	i;
	double	j;
	double	u;
	double	v;
	t_vec3	vp_horizontal; // ビューポート幅ベクトル
	t_vec3	vp_vertical; // ビューポート高さベクトル
	t_vec3	vp_lower_left_corner; // ビューポート左下隅
	t_vec3	vp_center; // ビューポート中心
	t_ray	ray;
	t_hit_record	*recs;
	recs = (t_hit_record *)ft_calloc(scene->n_objects, sizeof(t_hit_record));

	vp_center = camera->screen_center;
	vp_vertical = camera->screen_vertical;
	vp_horizontal = camera->screen_horizontal;
	vp_lower_left_corner = vp_center;
	vp_lower_left_corner = mr_vec3_sub(vp_lower_left_corner, mr_vec3_mul_double(vp_horizontal, 0.5));
	vp_lower_left_corner = mr_vec3_sub(vp_lower_left_corner, mr_vec3_mul_double(vp_vertical, 0.5));
	ray.origin = camera->camera.coodinates;
	vec3_debug(&ray.origin);
	vec3_debug(&camera->camera.coodinates);
	printf("vp_center: ");
	vec3_debug(&vp_center);
	printf("vp_horizontal: ");
	vec3_debug(&vp_horizontal);
	printf("vp_vertical: ");
	vec3_debug(&vp_vertical);
	printf("vp_lower_left_corner: ");
	vec3_debug(&vp_lower_left_corner);

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			u = i / (WIDTH);  // [0,1]
			v = j / (HEIGHT); // [0,1]
			// rayの方向ベクトル = (viewportの左下 + (水平方向ベクトル * u)) + (垂直方向ベクトル * v)) - rayの原点)
			t_vec3	ray_cross_screen = mr_vec3_add(
				mr_vec3_add(
					mr_vec3_mul_double(vp_vertical, v), mr_vec3_mul_double(vp_horizontal, u)
				),
				vp_lower_left_corner
			);
			if (scene->camera->fov == 0)
			{
				ray.origin = mr_vec3_sub(ray_cross_screen, scene->camera->direction);
				ray.direction = scene->camera->direction;
			}
			else
			{
				ray.direction = mr_vec3_sub(ray_cross_screen, ray.origin);
			}
			ray.pixel_x = i;
			ray.pixel_y = j;
			// printf("i = %f, j = %f\n", i, j);
			t_vec3	ray_c = ray_color(&ray, scene, recs);
			t_rgb	rgb = vec3_to_rgb(&ray_c);
			mr_mlx_pixel_put(img, i, j, rgb_to_color(&rgb));
			i += 1;
		}
		j += 1;
	}
}

static void	ray(t_img *img, t_scene *scene)
{
	t_viewport		camera;

	ft_bzero(&camera, sizeof(t_viewport));
	camera.camera.coodinates = scene->camera->position;
	camera.vp_height = 2.0;
	camera.vp_width = ASPECT_RATIO * camera.vp_height;
	if (scene->camera->fov == 0)
		camera.focal_length = 1;
	else
		camera.focal_length = camera.vp_width / (2 * tan(scene->camera->fov * M_PI / 180 / 2));
	camera.screen_horizontal.x = camera.vp_width;
	camera.screen_vertical.y = camera.vp_height;
	vec3_debug(&camera.screen_horizontal);
	camera.screen_horizontal = orient_vector(&camera.screen_horizontal, &scene->camera->direction);
	vec3_debug(&camera.screen_horizontal);
	vec3_debug(&camera.screen_vertical);
	camera.screen_vertical = orient_vector(&camera.screen_vertical, &scene->camera->direction);
	vec3_debug(&camera.screen_vertical);
	printf("scene->camera->position: "); vec3_debug(&scene->camera->position);
	camera.screen_center = mr_vec3_add(scene->camera->position, mr_vec3_mul_double(scene->camera->direction, camera.focal_length));
	printf("scene->camera->fov = %f(%d)\n", scene->camera->fov, scene->camera->fov == 0);
	printf("camera.focal_length = %f\n", camera.focal_length);
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
