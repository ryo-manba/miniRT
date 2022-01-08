/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:13:53 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/08 10:35:28 by corvvs           ###   ########.fr       */
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
	rec->t = t;
	rec->p = mr_vec3_add(ray->origin, mr_vec3_mul_double(&ray->direction, t));
	rec->hit = true;
	rt_after_hit(el, ray, rec);
	return (true);
}

static void	calc_equation(
		const t_element *el,
		const t_ray *ray,
		t_equation2 *eq)
{
	const t_vec3	q = mr_vec3_sub(ray->origin, el->position);
	const t_vec3	b = mr_vec3_mul_double(
					&ray->direction, cos(el->fov));
	const t_vec3	x = mr_vec3_mul_double(&q, cos(el->fov));
	const double	r = mr_vec3_dot(ray->direction, el->direction);
	const double	s = mr_vec3_dot(q, el->direction);

	eq->a = mr_vec3_dot(b, b) - r * r;
	eq->b_half = mr_vec3_dot(b, x) - r * s;
	eq->c = mr_vec3_dot(x, x) - s * s;
}

static bool	actual_hittest(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	t_equation2	eq;

	calc_equation(el, ray, &eq);
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
