/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 17:23:05 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/25 18:53:56 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	hit_cylinder_disc(
	const t_element *cylinder,
	const t_ray *ray,
	t_hit_record *rec,
	bool top)
{
	double		h;
	t_vec3		temp;
	t_element	disc;

	ft_memcpy(&disc, cylinder, sizeof(t_element));
	h = disc.height / 2;
	if (!top)
		disc.direction = mr_vec3_mul_double(&disc.direction, -1);
	rec->hit = false;
	disc.position = mr_vec3_add(disc.position, mr_vec3_mul_double(&disc.direction, h));
	if (rt_hittest_plane(&disc, ray, rec))
	{
		temp = mr_vec3_sub(rec->p, disc.position);
		rec->hit = (mr_vec3_length(&temp) < disc.diameter / 2);
	}
	rt_after_hit(&disc, ray, rec);
}

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
		rec->hit = true;
		t_vec3 axial_center = mr_vec3_add(
			el->position,
			mr_vec3_mul_double(
				&el->direction,
				axial_displacement
			)
		);
		t_vec3	temp;
		temp = mr_vec3_sub(rec->p, axial_center);
		rec->normal = mr_unit_vector(&temp);
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
	t_hit_record	hits[3];
	t_hit_record	*h;

	ft_bzero(hits, sizeof(t_hit_record) * 3);
	hit_cylinder_disc(el, ray, &hits[0], true);
	hit_cylinder_disc(el, ray, &hits[1], false);
	hit_cylinder_side(el, ray, &hits[2]);
	h = NULL;
	if (hits[0].hit)
		h = &hits[0];
	if (hits[1].hit && (!h || !h->hit || hits[1].t < h->t))
		h = &hits[1];
	if (hits[2].hit && (!h || !h->hit || hits[2].t < h->t))
		h = &hits[2];
	if (h)
		*rec = *h;
	return (!!h);
}
