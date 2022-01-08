/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:48:46 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/07 20:21:00 by corvvs           ###   ########.fr       */
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
bool			rt_hittest_paraboloid(
					const t_element *el,
					const t_ray *ray,
					t_hit_record *rec);

typedef bool	(*t_object_hit_tester)(
					const t_element *el,
					const t_ray *ray,
					t_hit_record *rec);

void			rt_set_tangent_plane(t_hit_record *rec);
void			rt_set_tangent_sphere(t_hit_record *rec);
void			rt_set_tangent_cylinder(t_hit_record *rec);
void			rt_set_tangent_cone(t_hit_record *rec);
void			rt_set_tangent_paraboloid(t_hit_record *rec);
void			rt_set_tangent_space(t_hit_record *rec);

typedef void	(*t_object_tangent_setter)(t_hit_record *rec);

t_vec3			rt_vec_tangent_to_global(
					t_hit_record *rec,
					t_vec3 *vtangent);

t_vec3			rt_bumpnormal(double u, double v, t_img *bumpmap);

#endif
