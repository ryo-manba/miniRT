/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_extractor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:35:51 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/01 12:23:39 by corvvs           ###   ########.fr       */
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

static const t_element_info_extractor	g_cylinder_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_scalar, // diameter
	extract_double_scalar, // height
	extract_double_vector, // color
	NULL,
};

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
	extract_double_scalar, // radius
	extract_double_vector, // color
	NULL,
};

static const t_element_info_extractor	g_plane_extractors[] = {
	extract_double_vector, // posiiton
	extract_double_vector, // direction
	extract_double_vector, // color
	NULL,
};

static bool	extract_seq(
	const char **words,
	void **addrs,
	const t_element_info_extractor *extractors)
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
		return (extract_seq(words, (void *[]){&(el->ratio), &(el->color)},
			g_ambient_extractors));
	if (el->etype == RD_ET_CAMERA)
		return (extract_seq(words, (void *[]){&(el->position), &(el->direction),
				&(el->fov)},
			g_camera_extractors));
	if (el->etype == RD_ET_LIGHT)
		return (extract_seq(words, (void *[]){&(el->position), &(el->ratio),
				&(el->color)},
			g_light_extractors));
	if (el->etype == RD_ET_SPHERE)
		return (extract_seq(words, (void *[]){&(el->position), &(el->radius),
				&(el->color)},
			g_sphere_extractors));
	if (el->etype == RD_ET_PLANE)
		return (extract_seq(words, (void *[]){&(el->position), &(el->direction),
				&(el->color)},
			g_plane_extractors));
	if (el->etype == RD_ET_CYLINDER)
		return (extract_seq(words, (void *[]){&(el->position), &(el->direction),
				&(el->diameter), &(el->height), &(el->color)},
			g_cylinder_extractors));
	return (false);
}

t_element	*rd_extract_element(
	t_element_type etype,
	const char **words)
{
	t_element	*el;

	el = (t_element *)ft_calloc(1, sizeof(t_element));
	if (!el)
	{
		return (NULL);
	}
	el->etype = etype;
	if (!extract_element(el, words))
	{
		free(el);
		return (NULL);
	}
	return (el);
}
