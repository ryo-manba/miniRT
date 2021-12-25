/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_extractor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:35:51 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/25 16:21:05 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static bool	extract_double_scalar(const char *str, void *slot)
{
	double	v;

	if (!str)
	{
		return (false);
	}
	v = rd_str_to_double(str);
	*(double *)slot = v;
	return (rd_is_finite(v));
}

static bool	extract_double_vector(const char *str, void *slot)
{
	t_vec3	*vecslot;

	if (!str)
		return (false);
	vecslot = (t_vec3 *)slot;
	rd_vectorize(str, vecslot);
	return (rd_is_finite(vecslot->x));
}

static const t_element_info_extractor	g_ambient_extractors[] = {
	extract_double_scalar, // ratio
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_camera_extractors[] = {
	extract_double_vector, // position
	extract_double_vector, // direction
	extract_double_scalar, // fov
	NULL,
};

static const t_element_info_extractor	g_light_extractors[] = {
	extract_double_vector, // position
	extract_double_scalar, // ratio
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_sphere_extractors[] = {
	extract_double_vector, // position
	extract_double_scalar, // diameter
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_plane_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_cylinder_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_scalar, // diameter
	extract_double_scalar, // height
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_cone_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_scalar, // fov
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_spotlight_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_scalar, // fov
	extract_double_vector, // color
	NULL,
};

static bool	extract_seq(
	const char **words,
	const t_element_info_extractor *extractors,
	void **addrs)
{
	size_t	i;

	i = 0;
	while (words[i + 1])
	{
		if (!(extractors[i])(words[i + 1], addrs[i]))
			return (false);
		i += 1;
	}
	return (true);
}

static bool	extract_element(
	t_element *el,
	const char **words)
{
	if (el->etype == RD_ET_AMBIENT)
		return (extract_seq(words, g_ambient_extractors,
				(void *[]){&(el->ratio), &(el->color)}));
	if (el->etype == RD_ET_CAMERA)
		return (extract_seq(words, g_camera_extractors,
				(void *[]){&(el->position), &(el->direction), &(el->fov)}));
	if (el->etype == RD_ET_LIGHT)
		return (extract_seq(words, g_light_extractors,
				(void *[]){&(el->position), &(el->ratio), &(el->color)}));
	if (el->etype == RD_ET_SPHERE)
		return (extract_seq(words, g_sphere_extractors,
				(void *[]){&(el->position), &(el->diameter), &(el->color)}));
	if (el->etype == RD_ET_PLANE)
		return (extract_seq(words, g_plane_extractors,
				(void *[]){&(el->position), &(el->direction), &(el->color)}));
	if (el->etype == RD_ET_CYLINDER)
		return (extract_seq(words, g_cylinder_extractors,
				(void *[]){&(el->position), &(el->direction),
				&(el->diameter), &(el->height), &(el->color)}));
	if (el->etype == RD_ET_CONE)
		return (extract_seq(words, g_cone_extractors,
				(void *[]){&(el->position), &(el->direction),
				&(el->diameter), &(el->height), &(el->color)}));
	if (el->etype == RD_ET_SPOTLIGHT)
		return (extract_seq(words, g_spotlight_extractors,
				(void *[]){&(el->position), &(el->direction),
				&(el->fov), &(el->color)}));
	return (false);
}

t_element	*rd_extract_element(
	t_element_type etype,
	const char **words)
{
	t_element	*el;
	double		r;

	el = (t_element *)ft_calloc(1, sizeof(t_element));
	if (!el)
		return (NULL);
	el->etype = etype;
	if (!extract_element(el, words))
	{
		free(el);
		return (NULL);
	}
	el->radius = el->diameter / 2;
	r = sqrt(el->direction.x * el->direction.x
			+ el->direction.y * el->direction.y
			+ el->direction.z * el->direction.z);
	if (r == 0)
		r = 1;
	el->direction.x /= r;
	el->direction.y /= r;
	el->direction.z /= r;
	el->color.x /= 255;
	el->color.y /= 255;
	el->color.z /= 255;
	return (el);
}
