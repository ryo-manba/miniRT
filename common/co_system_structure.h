/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_system_structure.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:02:10 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 20:23:42 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CO_SYSTEM_STRUCTURE_H
# define CO_SYSTEM_STRUCTURE_H

# include <stdlib.h>
# include "co_geometric_structure.h"
# include "co_object_structure.h"
# include "co_image_structure.h"
# define LIGHT_DISTANCE_DECAY 5e-2

typedef struct s_optics
{
	double		screen_height;
	double		screen_width;
	double		focal_length;
	t_vec3		screen_center;
	t_vec3		screen_horizontal;
	t_vec3		screen_vertical;
	t_vec3		screen_bottomleft;
}	t_optics;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	marking_color;
	bool	for_shadow;
	double	subpx;
}	t_ray;

typedef struct s_hit_record
{
	t_vec3		p;
	t_vec3		normal;
	double		t;
	bool		hit;
	double		cos;
	t_vec3		color;
	t_element	element;

	t_vec3		u0;
	t_vec3		v0;
	t_vec3		w0;
	double		u;
	double		v;
}	t_hit_record;

typedef struct s_scene
{
	t_element		*ambient;
	t_element		*camera;
	size_t			n_lights;
	size_t			n_objects;
	size_t			n_spotlights;
	t_element		**lights;
	t_element		**objects;
	t_element		**spotlights;
	t_optics		optics;
	t_hit_record	**recss;
	double			aspect_ratio;
	double			pixel_width;
	double			pixel_height;
	int				threads;
}	t_scene;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_scene	*scene;
}	t_info;

typedef struct s_subscene
{
	int				i;
	t_info			*info;
	t_hit_record	*recs;
}	t_subscene;

#endif
