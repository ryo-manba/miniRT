/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 02:39:32 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 12:38:54 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// returns vector from source of light to collision point.
t_vec3	rt_get_incident_vector(
	const t_hit_record *rec,
	const t_element *light,
	bool inversed)
{
	if (light->etype == RD_ET_SUNLIGHT)
	{
		if (inversed)
			return (light->direction);
		else
			return (mr_vec3_mul_double(&light->direction, -1));
	}
	else
	{
		if (inversed)
			return (mr_vec3_sub(light->position, rec->p));
		else
			return (mr_vec3_sub(rec->p, light->position));
	}
}
