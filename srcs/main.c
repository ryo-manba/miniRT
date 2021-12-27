/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:00:14 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/27 20:22:36 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_scene.h"
#include "mr_vec3.h"
#include "mr_utils.h"
#include "mr_camera.h"

#define ASPECT_RATIO ((double)16.0 / 9.0)
//#define HEIGHT 400
#define HEIGHT 320
#define WIDTH (HEIGHT * ASPECT_RATIO)
#define _GREEN (t_vec3){79, 172, 135}
#define _BLACK (t_vec3){41, 37, 34}

static int	vec3_to_color(const t_vec3 *v3)
{
	return (rt_create_trgb(0, (int)(v3->x * 255), (int)(v3->y * 255), (int)(v3->z * 255)));
}

static t_vec3	sky_blue(const t_vec3 direction)
{
	const t_vec3 c2 = {1.0, 1.0, 1.0}; // 白
	const t_vec3 c1 = {0.5, 0.7, 1.0}; // 青
	const t_vec3 unit_direction = mr_unit_vector(&direction);
	const double t = 0.5  * (unit_direction.y + 1.0);

	return (mr_vec3_add(
			mr_vec3_mul_double(&c1, t),
			mr_vec3_mul_double(&c2, 1 - t)));
}

bool	rt_hit_object(
	t_element *el,
	const t_ray *ray,
	t_hit_record *rec
)
{
	rec->hit = false;
	if (el->etype == RD_ET_SPHERE)
		return (rt_hittest_sphere(el, ray, rec));
	if (el->etype == RD_ET_PLANE)
		return (rt_hittest_plane(el, ray, rec));
	if (el->etype == RD_ET_CYLINDER)
		return (rt_hittest_cylinder(el, ray, rec));
	if (el->etype == RD_ET_CONE)
		return (rt_hittest_cone(el, ray, rec));
	return (false);
}

static void mr_normalize_color(t_vec3 *p)
{
	p->x /= 255.0;
	p->y /= 255.0;
	p->z /= 255.0;
}

/** m_freq:
 *  plane    :  0.5
 *  cylinder : 10.0
 *  sphere   : 10.0
 */ 
static t_vec3	checker_texture(const t_hit_record *rec)
{
	const double u = rec->tex.u;
	const double v = rec->tex.v;
	const double m_freq = 10; // 周波数; 1周当たりのブロック数
	const int sines = (int)(floor(m_freq * u) + floor(m_freq * v));

	if (sines % 2 == 0)
	{
		t_vec3 odd = _GREEN;
		mr_normalize_color(&odd);
		return (odd);
	}
	else
	{
		t_vec3 even = _BLACK;
		mr_normalize_color(&even);
		return (even);
	}
}

static t_vec3	light_proc(
	t_ray *r,
	t_scene *scene,
	const t_hit_record *actual,
	t_element *light
)
{
	t_vec3	base_color;

	mr_vec3_init(&base_color, 0, 0, 0);
	if (actual->hit && !rt_is_shadow(actual, light, scene, r))
	{
		t_vec3	color = mr_vec3_mul_double(&light->color, light->ratio);
		base_color = mr_vec3_add(base_color, rt_diffuse(actual, light, &color));
		base_color = mr_vec3_add(base_color, rt_specular(actual, &light->position, &color, r));
	}
	// else
	// 	return r->marking_color;
	return (base_color);
}

static t_vec3	reflection(
	t_ray *r,
	t_scene *scene,
	const t_hit_record *actual
)
{
	size_t	i;
	t_vec3	base_color;

	base_color = rt_ambient(scene->ambient->ratio,
		&scene->ambient->color, &actual->color);
	(void)checker_texture(actual);
	i = 0;
	while (i < scene->n_spotlights)
	{
		base_color = mr_vec3_add(base_color,
			light_proc(r, scene, actual, scene->spotlights[i]));
		i += 1;
	}
	i = 0;
	while (i < scene->n_lights)
	{
		base_color = mr_vec3_add(base_color,
			light_proc(r, scene, actual, scene->lights[i]));
		i += 1;
	}
	return (base_color);
}

static t_vec3	ray_color(t_ray *r, t_scene *scene)
{
	t_hit_record	*actual;
	size_t			i;

	ft_bzero(scene->recs, scene->n_objects * sizeof(t_hit_record));
	actual = NULL;
	i = 0;
	while (i < scene->n_objects)
	{
		if (rt_hit_object(scene->objects[i], r, &scene->recs[i]))
		{
			if (scene->recs[i].hit && (!actual || scene->recs[i].t < actual->t))
			{
				actual = &scene->recs[i];
			}
		}
		i += 1;
	}
	if (!actual)
	{
		return (sky_blue(r->direction));
	}

	t_element		*light;
	light = scene->lights[0];
	t_vec3 base_color = {0,0,0};
	if (actual->element.etype == RD_ET_PLANE)
		rt_set_tangent_plane(actual);
	else if (actual->element.etype == RD_ET_SPHERE)
		rt_set_tangent_sphere(actual);
	else if (actual->element.etype == RD_ET_CYLINDER)
		rt_set_tangent_cylinder(actual);
	else if (actual->element.etype == RD_ET_CONE)
		rt_set_tangent_cone(actual);
	const t_hit_record	actual_0 = *actual;
	t_vec3 ray_color = reflection(r, scene, &actual_0);
	base_color = mr_vec3_add(base_color, ray_color);
	base_color.x = fmin(base_color.x, 1);
	base_color.y = fmin(base_color.y, 1);
	base_color.z = fmin(base_color.z, 1);
	return (base_color);

}

static void	ray_loop(
	t_img *img,
	t_scene *scene)
{
	double	i;
	double	j;
	t_ray	ray;
	scene->recs = (t_hit_record *)malloc(scene->n_objects * sizeof(t_hit_record));

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			// rayの方向ベクトル = (viewportの左下 + (水平方向ベクトル * u)) + (垂直方向ベクトル * v)) - rayの原点)
			t_vec3	ray_cross_screen = mr_vec3_add(
				mr_vec3_add(
					mr_vec3_mul_double(&scene->optics.screen_vertical, (HEIGHT - j) / HEIGHT),
					mr_vec3_mul_double(&scene->optics.screen_horizontal, i / WIDTH)
				),
				scene->optics.screen_bottomleft
			);
			if (scene->camera->fov == 0)
			{
				ray.origin = mr_vec3_sub(ray_cross_screen, scene->camera->direction);
				ray.direction = scene->camera->direction;
			}
			else
			{
				ray.origin = scene->camera->position;
				ray.direction = mr_vec3_sub(ray_cross_screen, ray.origin);
			}
			ray.pixel_x = i;
			ray.pixel_y = j;
			t_vec3	ray_c = ray_color(&ray, scene);
			mr_mlx_pixel_put(img, i, j, vec3_to_color(&ray_c));
			i += 1;
		}
		j += 1;
	}
}


static void	ray(t_img *img, t_scene *scene)
{
	t_optics	*opt;
	t_element	*cam;

	opt = &scene->optics;
	cam = scene->camera;
	opt->screen_width = 2.0;
	opt->screen_height = opt->screen_width / ASPECT_RATIO;
	if (scene->camera->fov == 0)
		opt->focal_length = 1;
	else
		opt->focal_length = opt->screen_width / (2 * tan(cam->fov * M_PI / 360));
	opt->screen_horizontal.x = opt->screen_width;
	opt->screen_vertical.y = opt->screen_height;
	opt->screen_horizontal = rt_orient_vector(&opt->screen_horizontal, &cam->direction);
	opt->screen_vertical = rt_orient_vector(&opt->screen_vertical, &cam->direction);
	opt->screen_center = mr_vec3_add(cam->position,
							mr_vec3_mul_double(&cam->direction, opt->focal_length));
	opt->screen_bottomleft = mr_vec3_sub(
										mr_vec3_sub(
											opt->screen_center,
											mr_vec3_mul_double(&opt->screen_horizontal, 0.5)
										), mr_vec3_mul_double(&opt->screen_vertical, 0.5));
	ray_loop(img, scene);
}

static void	setup_info(t_info *info)
{
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "miniRT");
	info->img.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->img.addr = mlx_get_data_addr(
		info->img.img,
		&info->img.bpp,
		&info->img.line_len,
		&info->img.endian);
}

int main(int argc, char **argv)
{
	t_info	info;
	t_scene	scene;

	// xpmファイルの読み込みにmlxが必要なので、大変遺憾ながらここでmlxをセットアップする
	setup_info(&info);
	if (argc < 2 || rd_read_scene(argv[1], &scene) == false)
	{
		printf("Error\n");
		return (1);
	}
	t_img		bumpmap_image;
	bumpmap_image.img = mlx_xpm_file_to_image(info.mlx, "images/terrain.xpm", &bumpmap_image.width, &bumpmap_image.height);
	bumpmap_image.addr = mlx_get_data_addr(
		bumpmap_image.img,
		&bumpmap_image.bpp,
		&bumpmap_image.line_len,
		&bumpmap_image.endian);
	printf("(%d, %d)\n", bumpmap_image.width, bumpmap_image.height);
	size_t	i = 0;
	while (i < scene.n_objects)
		scene.objects[i++]->bumpmap = &bumpmap_image;

	ray(&info.img, &scene);
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	mlx_hook(info.win, 17, 1L << 17, &mr_exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}	
