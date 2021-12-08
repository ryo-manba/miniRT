/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_read.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:45:06 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/08 15:41:17 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MR_READ_H
# define MR_READ_H

# include <stdlib.h>
# include <stdbool.h>
# include "../mr_vec3.h"

typedef enum e_element_type
{
	RD_ET_DUMMY,
	RD_ET_AMBIENT,
	RD_ET_CAMERA,
	RD_ET_LIGHT,
	RD_ET_SPHERE,
	RD_ET_PLANE,
	RD_ET_CYLINDER,
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
}	t_element;

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
	t_element	**lights;
	t_element	**objects;
	t_optics	optics;
}	t_scene;

bool	rd_read_scene(const char *filename, t_scene *scene);
void	rd_destroy_scene(t_scene *scene);
double	rd_inf(bool positive);

#endif
