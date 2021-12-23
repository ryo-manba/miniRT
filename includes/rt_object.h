/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:48:46 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/23 16:41:27 by rmatsuka         ###   ########.fr       */
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

typedef bool	(*t_object_hit_tester)(
			const t_element *el,
			const t_ray *ray,
			t_hit_record *rec);

#endif
