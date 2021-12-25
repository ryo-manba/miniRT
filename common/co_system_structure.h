/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_system_structure.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:02:10 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/25 16:24:15 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CO_SYSTEM_STRUCTURE_H
# define CO_SYSTEM_STRUCTURE_H

# include <stdlib.h>
# include "co_geometric_structure.h"
# include "co_object_structure.h"

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

typedef struct s_scene
{
	t_element	*ambient;
	t_element	*camera;
	size_t		n_lights;
	size_t		n_objects;
	size_t		n_spotlights;
	t_element	**lights;
	t_element	**objects;
	t_element	**spotlights;
	t_optics	optics;
}	t_scene;

#endif
