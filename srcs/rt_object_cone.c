/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:13:53 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/23 11:50:04 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	t_predicate(
	const t_element *el,
	const t_ray *ray,
	const double t,
	t_hit_record *rec
)
{
	printf("t = %f\n", t);
	if (t < 1)
		return (false);
	const t_vec3 p = mr_vec3_add(ray->origin, mr_vec3_mul_double(&ray->direction, t));
	const t_vec3 pc = mr_vec3_sub(p, el->position);
	if (mr_vec3_dot(pc, el->direction) < 0)
		return (false);
	rec->t = t;
	rec->p = p;
	rec->hit = true;

	vec3_debug((t_vec3 *)&p);
	printf("2 * acos((p - c) / ||p - c|| . d) = %f\n", 180 / M_PI * 2 * acos(mr_vec3_dot(pc, el->direction) / mr_vec3_length(&pc)));
	rec->normal = mr_vec3_sub(
		el->direction,
		mr_vec3_mul_double(&pc, cos(el->fov * M_PI / 360) / mr_vec3_length(&pc))
	);
	rec->normal = mr_unit_vector(&rec->normal);

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
	// assuming B^2 != R^2
	const double a = BB - R * R;
	const double b = BQ - R * S;
	const double discriminant = b * b - a * (QQ - S * S);
	if (discriminant < 0)
		return (false);
	const double t1 = (-b - sqrt(discriminant)) / a;
	if (t_predicate(el, ray, t1, rec))
		return (true);
	const double t2 = (-b + sqrt(discriminant)) / a;
	if (t_predicate(el, ray, t2, rec))
		return (true);
	return (false);
}

bool	rt_hittest_cone(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	printf("rt_hittest_cone\n");
	if (actual_hittest(el, ray, rec))
	{
		printf("yes: t = %f\n", rec->t);
		return (true);
	}
	else
	{
		printf("no\n");
		return (false);
	}
}
