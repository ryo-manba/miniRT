/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:48:46 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/27 14:13:01 by corvvs           ###   ########.fr       */
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

void	rt_set_tangent_plane(t_hit_record *rec);
void	rt_set_tangent_sphere(t_hit_record *rec);
void	rt_set_tangent_cylinder(t_hit_record *rec);
void	rt_set_tangent_cone(t_hit_record *rec);

t_vec3	rt_vec_tangent_to_global(
	t_hit_record *rec,
	t_vec3 *vtangent
);

t_vec3	test_bumpfunc_wave2(double u, double v);
t_vec3	test_bumpfunc_image(double u, double v);

#endif
