/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 02:39:32 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 02:45:58 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// returns vector from source of light to collision point.
t_vec3	rt_get_incident_vector(
	const t_hit_record *rec,
	const t_element *light)
{
	if (light->etype == RD_ET_SUNLIGHT)
		return (light->direction);
	else
		return (mr_vec3_sub(rec->p, light->position));
}
