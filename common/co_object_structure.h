/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_object_structure.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:02:10 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/31 12:03:41 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CO_OBJECT_STRUCTURE_H
# define CO_OBJECT_STRUCTURE_H

# include "co_geometric_structure.h"
# include "co_image_structure.h"
# include <stdlib.h>

typedef enum e_element_type
{
	RD_ET_DUMMY,
	RD_ET_AMBIENT,
	RD_ET_CAMERA,
	RD_ET_LIGHT,
	RD_ET_SPHERE,
	RD_ET_PLANE,
	RD_ET_CYLINDER,
	RD_ET_CONE,
	RD_ET_SPOTLIGHT,
	RD_ET_UNEXPECTED,
}	t_element_type;

typedef struct s_element
{
	t_element_type		etype;
	t_vec3				position;
	t_vec3				direction;
	t_vec3				color;
	double				ratio;
	double				radius;
	double				diameter;
	double				height;
	double				fov;
	struct s_element	*next;
	size_t				id;
	t_img				*texture;
	t_img				*bumpmap;
}	t_element;

#endif
