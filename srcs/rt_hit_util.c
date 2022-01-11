/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:29:15 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/10 09:09:41 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rt_hit_point(double t, const t_ray *ray)
{
	return (mr_vec3_add((ray->origin),
			(mr_vec3_mul_double(&ray->direction, t))));
}

void	rt_after_hit(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	if (rec->hit)
	{
		rec->element = *el;
		rec->cos = mr_vec3_dot(mr_unit_vector(&ray->direction), rec->normal);
	}
	else
	{
		rec->t = rd_inf(true);
	}
}

static const t_object_hit_tester	g_hit_testers[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	rt_hittest_sphere,
	rt_hittest_plane,
	rt_hittest_cylinder,
	rt_hittest_paraboloid,
	rt_hittest_cone,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	};

bool	rt_hit_object(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec
)
{
	const t_object_hit_tester	hit_tester = g_hit_testers[el->etype];

	rec->hit = false;
	if (!hit_tester)
		return (false);
	return (hit_tester(el, ray, rec));
}

t_hit_record	*rt_find_actual_hit(t_ray *r, t_scene *scene)
{
	t_hit_record	*actual;
	size_t			i;

	ft_bzero(scene->recs, scene->n_objects * sizeof(t_hit_record));
	i = 0;
	actual = NULL;
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
	return (actual);
}
