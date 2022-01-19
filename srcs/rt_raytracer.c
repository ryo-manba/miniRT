/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 10:16:29 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 20:29:48 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t_ray *ray, t_subscene *subscene, int x, int y)
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
			set_ray_for_pixel(subscene->info->scene, ray,
				(x + (j + 0.5) / ray->subpx), (y + (i + 0.5) / ray->subpx));
			actual = rt_find_actual_hit(ray, subscene);
			if (actual)
				mr_vec3_add_comp(&bc, rt_reflect_ray(ray, subscene, actual));
			else
				mr_vec3_add_comp(&bc, rt_sky_blue(ray->direction));
			j += 1;
		}
		i += 1;
	}
	mr_vec3_mul_double_comp(&bc, 1 / (ray->subpx * ray->subpx));
	return (mr_vec_cutoff(bc));
}

void	*subraytrace(void *data)
{
	int			x;
	int			y;
	t_ray		ray;
	t_vec3		color;
	t_subscene	*subscene;

	subscene = (t_subscene *)data;
	ray.for_shadow = false;
	ray.subpx = SUBPIXEL;
	y = subscene->i;
	while (y < subscene->info->scene->pixel_height)
	{
		x = 0;
		while (x < subscene->info->scene->pixel_width)
		{
			color = derive_color_for_pixel(&ray, subscene, x, y);
			mr_mlx_pixel_put(&subscene->info->img, x, y, color);
			x += 1;
		}
		y += subscene->info->scene->threads;
	}
	return (NULL);
}

#ifdef BONUS
void	rt_raytrace(t_info *info, t_scene *scene)
{
	t_subscene	subscenes[THREADS];
	pthread_t	threads[THREADS];
	int			i;

	scene->threads = THREADS;
	ft_bzero(&threads, sizeof(pthread_t) * THREADS);
	i = 0;
	while (i < THREADS)
	{
		subscenes[i].i = i;
		subscenes[i].info = info;
		subscenes[i].recs = scene->recss[i];
		pthread_create(&threads[i], NULL, subraytrace,
			&subscenes[i]);
		i += 1;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		i += 1;
	}
}

#else
void	rt_raytrace(t_info *info, t_scene *scene)
{
	t_subscene	subscene;

	scene->threads = 1;
	subscene.i = 0;
	subscene.info = info;
	subscene.recs = scene->recss[0];
	subraytrace(&subscene);
}
#endif
