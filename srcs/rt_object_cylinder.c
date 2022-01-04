/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 17:23:05 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/26 23:31:07 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_at(
	const t_element *el,
	double t,
	const t_ray *ray,
	t_hit_record *rec)
{
	rec->t = t;
	rec->p = rt_hit_point(rec->t, ray);
	double axial_displacement = mr_vec3_dot(
		mr_vec3_sub(rec->p, el->position), el->direction
	);
	if (t < 1 || fabs(axial_displacement) >= el->height / 2)
		rec->hit = false;
	else
	{
		rec->normal.x = axial_displacement;
		rec->hit = true;
		rt_after_hit(el, ray, rec);
	}
	return (rec->hit);
}

static void	hit_cylinder_side(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	t_vec3 oc = mr_vec3_sub(ray->origin, el->position);
	double oc2 = mr_vec3_dot(oc, oc);
	double b2 = mr_vec3_dot(ray->direction, ray->direction);
	double d2 = mr_vec3_dot(el->direction, el->direction);
	double bd = mr_vec3_dot(ray->direction, el->direction);
	double oc_b = mr_vec3_dot(oc, ray->direction);
	double oc_d = mr_vec3_dot(oc, el->direction);
	t_equation2	eq;

	eq.a = b2 * d2 - bd * bd;
	eq.b_half = (oc_b * d2 - oc_d * bd);
	eq.c = oc2 * d2 - oc_d * oc_d - el->diameter * el->diameter / 4;
	if (rt_solve_equation2(&eq) < 1)
		return ;
	if (!hit_at(el, eq.t1, ray, rec) && !hit_at(el, eq.t2, ray, rec))
		rec->hit = false;
}

bool	rt_hittest_cylinder(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	ft_bzero(rec, sizeof(t_hit_record));
	hit_cylinder_side(el, ray, rec);
	return (rec->hit);
}
