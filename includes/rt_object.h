/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:48:46 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/26 20:10:16 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJECT_H
# define RT_OBJECT_H

# include <limits.h>
# include "mr_read.h"
# include "rt_scene.h"
# include "mr_common.h"

bool			rt_hittest_sphere(
					const t_element *el,
					const t_ray *ray,
					t_hit_record *rec);
bool			rt_hittest_plane(
					const t_element *el,
					const t_ray *ray,
					t_hit_record *rec);
bool			rt_hittest_cylinder(
					const t_element *el,
					const t_ray *ray,
					t_hit_record *rec);
bool			rt_hittest_cone(
					const t_element *el,
					const t_ray *ray,
					t_hit_record *rec);

typedef bool	(*t_object_hit_tester)(
			const t_element *el,
			const t_ray *ray,
			t_hit_record *rec);

void	rt_setnormal_plane(t_hit_record *rec);
void	rt_setnormal_sphere(t_hit_record *rec);
void	rt_setnormal_cylinder(t_hit_record *rec);
void	rt_setnormal_cone(t_hit_record *rec);


#endif
