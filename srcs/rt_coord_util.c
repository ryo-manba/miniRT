/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_coord_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:56:27 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/12 02:08:49 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define EPS 1e-6

// for a given unit vector,
// find some unit vector orthogonal for it.
t_vec3	rt_coord_perpendicular_unit(const t_vec3 *u)
{
	t_vec3	ud;
	t_vec3	dd;

	ud = (t_vec3){1, 0, 0};
	dd = mr_vec3_cross(u, &ud);
	if (fabs(mr_vec3_length_squared(&dd)) > EPS)
		return (mr_unit_vector(&dd));
	ud = (t_vec3){0, 1, 0};
	dd = mr_vec3_cross(u, &ud);
	if (fabs(mr_vec3_length_squared(&dd)) > EPS)
		return (mr_unit_vector(&dd));
	ud = (t_vec3){0, 0, 1};
	dd = mr_vec3_cross(u, &ud);
	return (mr_unit_vector(&dd));
}

// for a given vector u and a unit vector n,
// returns a vector that rotate u 90-degrees around n.
t_vec3	rt_coord_turn_around_90(const t_vec3 *u, const t_vec3 *n)
{
	return (mr_vec3_add(
			mr_vec3_mul_double(n, mr_vec3_dot(*n, *u)),
			mr_vec3_cross(n, u)
		));
}
