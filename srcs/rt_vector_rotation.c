/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:10:16 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/14 21:20:11 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mr_vec3.h"
#include <math.h> 

// get azimuth-angle with y-axis-up
static double	get_azimuth(const t_vec3 *vec)
{
	const double	phi = atan2(vec->x, vec->z);

	if (vec->z >= 0)
		return (phi);
	return (phi);
}

// get elevation-angle with y-axis-up
static double	get_elevation(const t_vec3 *vec)
{
	const double	x = sqrt(vec->x * vec->x + vec->z * vec->z);
	const double	theta = atan2(vec->y, x);

	return (theta);
}

// transform a vector v by transformation
// that takes the vector (0, 0, +1) to vector orient.
t_vec3	rt_orient_vector(const t_vec3 *v, const t_vec3 *orient)
{
	const t_vec3	az_axis = {0, 1, 0};
	const t_vec3	el_axis = {-1, 0, 0};
	const double	az = get_azimuth(orient);
	const t_vec3	v2 = mr_rot_around_axis(v, &az_axis, az);
	const t_vec3	el_axis2 = mr_rot_around_axis(&el_axis, &az_axis, az);

	return (mr_rot_around_axis(&v2, &el_axis2, get_elevation(orient)));
}
