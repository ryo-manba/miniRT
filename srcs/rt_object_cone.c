/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:13:53 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/02 18:20:51 by corvvs           ###   ########.fr       */
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
	const double	T = cos(el->fov * M_PI / 360);
	const t_vec3	q = mr_vec3_sub(ray->origin, el->position);
	const t_vec3	B = mr_vec3_mul_double(&ray->direction, T);
	const double	BB = mr_vec3_dot(B, B);
	const t_vec3	Q = mr_vec3_mul_double(&q, T);
	const double	QQ = mr_vec3_dot(Q, Q);
	const double	BQ = mr_vec3_dot(B, Q);
	const double	R = mr_vec3_dot(ray->direction, el->direction);
	const double	S = mr_vec3_dot(q, el->direction);
	
	t_equation2	eq;
	eq.a = BB - R * R;
	eq.b_half = (BQ - R * S);
	eq.c = QQ - S * S;
	rt_solve_equation2(&eq);
	if (eq.solutions >= 1 && t_predicate(el, ray, eq.t1, rec))
		return (true);
	if (eq.solutions >= 2 && t_predicate(el, ray, eq.t2, rec))
		return (true);
	return (false);
}

bool	rt_hittest_cone(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	if (!actual_hittest(el, ray, rec))
		return (false);
	return (true);
}
