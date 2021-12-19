/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:14:54 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/14 18:57:59 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	t_vec3	calc_perpendicular(t_vec3 *normal)
{
	t_vec3	p; // 平面の法線ベクトルに垂直な単位ベクトル

	if (normal->x != 0)
	{
		p.y = 0;
		p.z = sqrt(1 / (1 + pow((normal->z / normal->x), 2)));
		p.x = -normal->z / normal->x * p.z;
	}
	else if (normal->z != 0.0)
	{
		p.y = 0;
		p.x = sqrt(1 / (1 + pow((normal->x / normal->z), 2)));
		p.z = -normal->x / normal->z * p.x;
	}
	else
	{
		p.z = 0;
		p.x = sqrt(1 / (1 + pow((normal->x / normal->y), 2)));
		p.y = -normal->x / normal->y * p.x;
	}
	return (p);
}


static void	rt_texture_plane(t_hit_record *rec)
{
	t_vec3	p1;
	t_vec3	p2; // p1をnの周りに90度回した単位ベクトルp2を用意する
	t_vec3	n = rec->normal;

	p1 = calc_perpendicular(&rec->normal);
	// p2 = n(n・p1) + n × p1
	t_vec3 temp1 = (mr_vec3_mul_double(&n , mr_vec3_dot(n, p1)));
	t_vec3 temp2 = mr_vec3_cross(&n, &p1);

	p2 = mr_vec3_add(temp1, temp2);
	t_vec3 q = rec->p; //平面の基準点
	t_vec3 p0 = rec->element.position;

	rec->tex.u = mr_vec3_dot(mr_vec3_sub(q, p0), p1);
	rec->tex.v = mr_vec3_dot(mr_vec3_sub(q, p0), p2);
}

bool	rt_hittest_plane(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	const t_vec3	oc = mr_vec3_sub(el->position, ray->origin);
	const double	den = mr_vec3_dot(oc, el->direction);
	const double	num = mr_vec3_dot(ray->direction, el->direction);

	if (num == 0)
		return (false);
	rec->t = den / num;
	rec->p = rt_hit_point(rec->t, ray);
	if (rec->t < 1)
		return (false);
	rec->normal = el->direction;
	rec->hit = true;

	// !!BONUS
	rt_texture_plane(rec);
	rt_after_hit(el, ray, rec);
	return (true);
}
