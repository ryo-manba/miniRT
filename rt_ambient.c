/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ambient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 23:28:57 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/22 23:30:01 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	mr_vec3_mul(const t_vec3 *u, const t_vec3 *v)
{
	t_vec3	mul;

	mul.x = u->x * v->x;
	mul.y = u->y * v->y;
	mul.z = u->z * v->z;
	return (mul);
}

t_vec3	rt_ambient(
	const double ratio,
	const t_vec3 *ambient_color,
	const t_vec3 *obj_color)
{
	const t_vec3	ambient = mr_vec3_mul_double(ambient_color, ratio);

	return (mr_vec3_mul(&ambient, obj_color));
}
