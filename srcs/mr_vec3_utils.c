/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_vec3_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:41:09 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/14 21:20:15 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mr_vec3.h"

double	mr_vec3_length_squared(const t_vec3 *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}

double	mr_vec3_length(const t_vec3 *v)
{
	return (sqrt(mr_vec3_length_squared(v)));
}

t_vec3	mr_vec3_mul_double(const t_vec3 *u, const double t)
{
	t_vec3	vec;

	vec.x = u->x * t;
	vec.y = u->y * t;
	vec.z = u->z * t;
	return (vec);
}

t_vec3	mr_unit_vector(const t_vec3 *v)
{
	return (mr_vec3_mul_double(v, 1.0 / mr_vec3_length(v)));
}

// rotate vector r around axis n with given angle.
t_vec3	mr_rot_around_axis(const t_vec3 *r, const t_vec3 *n,
	const double angle)
{
	t_vec3	temp;

	temp = mr_vec3_cross(n, r);
	mr_vec3_mul_double_comp(&temp, sin(angle));
	return (mr_vec3_add(
			mr_vec3_add(
				mr_vec3_mul_double(r, cos(angle)),
				mr_vec3_mul_double(
					n,
					mr_vec3_dot(*n, *r) * (1 - cos(angle))
				)
			), temp
		));
}
