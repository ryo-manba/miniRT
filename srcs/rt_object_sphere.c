/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:13:53 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/26 20:56:32 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	setup_hitequation(
	t_equation2 *eq,
	const t_element *el,
	const t_ray *ray
)
{
	const t_vec3	oc = mr_vec3_sub(ray->origin, el->position);

	eq->a = mr_vec3_length_squared(&ray->direction);
	eq->b_half = mr_vec3_dot(oc, ray->direction);
	eq->c = mr_vec3_length_squared(&oc) - el->radius * el->radius;
}

void	rt_set_tangent_sphere(
	t_hit_record *rec
)
{
	const t_vec3	y0 = {0, 1, 0};

	rec->normal = mr_vec3_sub(rec->p, rec->element.position);
	rec->normal = mr_unit_vector(&rec->normal);
	rec->w0 = rec->normal;
	rec->u0 = mr_vec3_cross(&rec->w0, &y0);
	rec->u0 = mr_unit_vector(&rec->u0);
	rec->v0 = mr_vec3_cross(&rec->w0, &rec->u0);
	t_vec3 vt = {0, 0, 1};
	rec->normal = rt_vec_tangent_to_global(rec, &vt);
}

bool	rt_hittest_sphere(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	t_equation2	eq;

	setup_hitequation(&eq, el, ray);
	if (rt_solve_equation2(&eq) < 1)
		return (false);
	rec->t = 0;
	if (eq.solutions >= 1 && eq.t1 >= 1)
		rec->t = eq.t1;
	else if (eq.solutions >= 2 && eq.t2 >= 1)
		rec->t = eq.t2;
	else
		return (false);
	rec->p = rt_hit_point(rec->t, ray);
	rec->hit = true;
	rt_texture_sphere(rec);
	rt_after_hit(el, ray, rec);
	return (true);
}
