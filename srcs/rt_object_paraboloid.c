/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_paraboloid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 00:02:39 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/05 21:07:01 by corvvs           ###   ########.fr       */
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
	if (t < 1)
		return (false);
	const t_vec3 p = mr_vec3_add(ray->origin, mr_vec3_mul_double(&ray->direction, t));
	rec->t = t;
	rec->p = p;
	rec->hit = true;
	rt_after_hit(el, ray, rec);
	return (true);
}

static bool actual_hittest(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	// 真の法線N
	t_vec3	q = mr_vec3_sub(ray->origin, el->position);
	t_vec3	g = mr_vec3_sub(ray->origin, el->focalpoint);
	t_vec3	N = el->direction;
	if (mr_vec3_dot(q, el->direction) < 0)
		N = mr_vec3_mul_double(&N, 1);
	double	bb = mr_vec3_length_squared(&ray->direction);
	double	bd = mr_vec3_dot(ray->direction, N);
	double	qd = mr_vec3_dot(q, N);
	t_equation2	eq;
	eq.a = bd * bd - bb;
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
