/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 10:16:29 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 16:56:45 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	sky_blue(const t_vec3 direction)
{
	const t_vec3	c2 = {1.0, 1.0, 1.0};
	const t_vec3	c1 = {0.5, 0.7, 1.0};
	const t_vec3	unit_direction = mr_unit_vector(&direction);
	const double	t = 0.5 * (unit_direction.y + 1.0);

	return (mr_vec3_add(
			mr_vec3_mul_double(&c1, t),
			mr_vec3_mul_double(&c2, 1 - t)));
}

static void	set_ray_for_pixel(t_scene *scene, t_ray *ray, double x, double y)
{
	const t_element	*cam = scene->camera;

	ray->origin = mr_vec3_add(
			mr_vec3_add(
				mr_vec3_mul_double(&scene->optics.screen_vertical,
					(scene->pixel_height - y) / scene->pixel_height),
				mr_vec3_mul_double(&scene->optics.screen_horizontal,
					x / scene->pixel_width)
				),
			scene->optics.screen_bottomleft
			);
	if (cam->fov == 0)
	{
		mr_vec3_sub_comp(&ray->origin, cam->direction);
		ray->direction = cam->direction;
	}
	else
	{
		ray->direction = mr_vec3_sub(ray->origin, cam->position);
		ray->origin = cam->position;
	}
}

static t_vec3	derive_color_for_pixel(
	t_ray *ray, t_scene *scene, int x, int y)
{
	t_hit_record	*actual;
	t_vec3			bc;
	double			i;
	double			j;

	i = 0;
	mr_vec3_init(&bc, 0, 0, 0);
	while (i < ray->subpx)
	{
		j = 0;
		while (j < ray->subpx)
		{
			set_ray_for_pixel(scene, ray,
				(x + (j + 0.5) / ray->subpx), (y + (i + 0.5) / ray->subpx));
			actual = rt_find_actual_hit(ray, scene);
			if (actual)
				mr_vec3_add_comp(&bc, rt_reflect_ray(ray, scene, actual));
			else
				mr_vec3_add_comp(&bc, sky_blue(ray->direction));
			j += 1;
		}
		i += 1;
	}
	mr_vec3_mul_double_comp(&bc, 1 / (ray->subpx * ray->subpx));
	return (mr_vec_cutoff(bc));
}

static void	setup_optics(t_scene *scene)
{
	t_optics		*opt;
	const t_element	*cam = scene->camera;

	opt = &scene->optics;
	opt->screen_width = 2.0;
	opt->screen_height = opt->screen_width / scene->aspect_ratio;
	if (scene->camera->fov == 0)
		opt->focal_length = 1;
	else
		opt->focal_length = opt->screen_width / (2 * tan(cam->fov));
	opt->screen_horizontal.x = opt->screen_width;
	opt->screen_vertical.y = opt->screen_height;
	opt->screen_horizontal
		= rt_orient_vector(&opt->screen_horizontal, &cam->direction);
	opt->screen_vertical
		= rt_orient_vector(&opt->screen_vertical, &cam->direction);
	opt->screen_center = mr_vec3_add(cam->position,
			mr_vec3_mul_double(&cam->direction, opt->focal_length));
	opt->screen_bottomleft = mr_vec3_sub(
			mr_vec3_sub(
				opt->screen_center,
				mr_vec3_mul_double(&opt->screen_horizontal, 0.5)
				), mr_vec3_mul_double(&opt->screen_vertical, 0.5));
}

void	rt_raytrace(t_info *info, t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_vec3	color;

	setup_optics(scene);
	ray.for_shadow = false;
	ray.subpx = SUBPIXEL;
	y = 0;
	while (y < scene->pixel_height)
	{
		x = 0;
		while (x < scene->pixel_width)
		{
			color = derive_color_for_pixel(&ray, scene, x, y);
			mr_mlx_pixel_put(&info->img, x, y, color);
			x += 1;
		}
		y += 1;
	}
}
