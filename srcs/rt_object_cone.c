/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:13:53 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/24 18:19:13 by corvvs           ###   ########.fr       */
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
	const t_vec3 pc = mr_vec3_sub(p, el->position);
	rec->t = t;
	rec->p = p;
	rec->hit = true;

	rec->normal = mr_vec3_sub(
		mr_vec3_mul_double(&pc, cos(el->fov * M_PI / 360) / mr_vec3_length(&pc)),
		el->direction
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
	const double c = QQ - S * S;
	if (fabs(a) < EPS)
	{
		if (fabs(b) < EPS)
			return (false);
		const double t0 = c / b / 2;
		if (t_predicate(el, ray, t0, rec))
		{
			return (true);
		}
		return (false);
	}
	const double discriminant = b * b - a * c;
	if (discriminant < 0)
		return (false);
	const double t1 = (-b - sqrt(discriminant)) / a;
	const double t2 = (-b + sqrt(discriminant)) / a;
	if (t_predicate(el, ray, t1, rec))
		return (true);
	if (t_predicate(el, ray, t2, rec))
		return (true);
	return (false);
}

void	rt_texture_cone(t_hit_record *rec, const t_element *el)
{
	const t_vec3	r = mr_vec3_sub(rec->p, el->position);
	const double	phi = mr_vec3_dot(el->direction, r);
	const t_vec3	u1 = rt_coord_perpendicular_unit(&el->direction);
	const t_vec3	u2 = rt_coord_turn_around_90(&u1, &el->direction);
	const double	dx = mr_vec3_dot(r, u1);
	const double	dz = mr_vec3_dot(r, u2);
	const double	theta = atan2(dz, dx);

	rec->tex.u = theta / M_PI;
	rec->tex.v = phi / (2 * M_PI);
}

bool	rt_hittest_cone(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	if (actual_hittest(el, ray, rec))
	{
		rt_texture_cone(rec, el);
		return (true);
	}
	else
	{
		return (false);
	}
}
