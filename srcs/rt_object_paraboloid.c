/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_paraboloid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 00:02:39 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/07 21:18:54 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EPS 1e-9

static bool	t_predicate(
	const t_element *el,
	const t_ray *ray,
	const double t,
	t_hit_record *rec
)
{
	t_vec3	p;

	if (t < 1)
		return (false);
	p = mr_vec3_add(ray->origin, mr_vec3_mul_double(&ray->direction, t));
	rec->t = t;
	rec->p = p;
	rec->hit = true;
	rt_after_hit(el, ray, rec);
	return (true);
}

static bool	actual_hittest(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	const t_vec3	q = mr_vec3_sub(ray->origin, el->position);
	const t_vec3	g = mr_vec3_sub(ray->origin, el->focalpoint);
	const double	bd = mr_vec3_dot(ray->direction, el->direction);
	const double	qd = mr_vec3_dot(q, el->direction);
	t_equation2		eq;

	eq.a = bd * bd - mr_vec3_length_squared(&ray->direction);
	eq.b_half = qd * bd - mr_vec3_dot(ray->direction, g);
	eq.c = qd * qd - mr_vec3_length_squared(&g);
	rt_solve_equation2(&eq);
	if (eq.solutions >= 1 && t_predicate(el, ray, eq.t1, rec))
		return (true);
	if (eq.solutions >= 2 && t_predicate(el, ray, eq.t2, rec))
		return (true);
	return (false);
}

bool	rt_hittest_paraboloid(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	if (!actual_hittest(el, ray, rec))
		return (false);
	return (true);
}
