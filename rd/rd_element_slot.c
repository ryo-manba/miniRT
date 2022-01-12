/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_element_slot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:14:43 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/12 11:40:48 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static void	**field_memcpy(
	void **dest,
	void **src
)
{
	size_t	i;

	i = 0;
	while (true)
	{
		dest[i] = src[i];
		if (!src[i])
			break ;
		i += 1;
	}
	return (dest);
}

static void	**element_pointers_bonus(
	void **dest,
	t_element *el)
{
	if (el->etype == RD_ET_PARABOLOID)
		return (field_memcpy(dest, (void *[]){&el->focalpoint, &el->position,
				&el->direction, &el->color, NULL}));
	if (el->etype == RD_ET_CONE)
		return (field_memcpy(dest, (void *[]){&el->position, &el->direction,
				&el->fov, &el->color, NULL}));
	if (el->etype == RD_ET_SPOTLIGHT)
		return (field_memcpy(dest, (void *[]){&el->position, &el->direction,
				&el->fov, &el->ratio, &el->color, NULL}));
	if (el->etype == RD_ET_TEXTURE)
		return (field_memcpy(dest, (void *[]){&el->xpm_file_path, &el->freq_u,
				&el->freq_v, NULL}));
	if (el->etype == RD_ET_BUMPMAP)
		return (field_memcpy(dest, (void *[]){&el->xpm_file_path, &el->height,
				&el->freq_u, &el->freq_v, NULL}));
	if (el->etype == RD_ET_CHECKER)
		return (field_memcpy(dest, (void *[]){&el->freq_u, &el->freq_v,
				&el->color, &el->subcolor, NULL}));
	if (el->etype == RD_ET_MATERIAL)
		return (field_memcpy(dest, (void *[]){&el->k_diffuse, &el->k_specular,
				&el->gloss, NULL}));
	return (NULL);
}

static void	**element_pointers_mandatory(
	void **dest,
	t_element *el)
{
	if (el->etype == RD_ET_AMBIENT)
		return (field_memcpy(dest, (void *[]){&el->ratio, &el->color, NULL}));
	if (el->etype == RD_ET_CAMERA)
		return (field_memcpy(dest, (void *[]){&el->position, &el->direction,
				&el->fov, NULL}));
	if (el->etype == RD_ET_LIGHT)
		return (field_memcpy(dest, (void *[]){&el->position, &el->ratio,
				&el->color, NULL}));
	if (el->etype == RD_ET_SPHERE)
		return (field_memcpy(dest, (void *[]){&el->position, &el->diameter,
				&el->color, NULL}));
	if (el->etype == RD_ET_PLANE)
		return (field_memcpy(dest, (void *[]){&el->position, &el->direction,
				&el->color, NULL}));
	if (el->etype == RD_ET_CYLINDER)
		return (field_memcpy(dest, (void *[]){&el->position, &el->direction,
				&el->diameter, &el->height, &el->color, NULL}));
	return (NULL);
}

void	**rd_get_element_slots(
	void **dest,
	t_element *el)
{
	void	**fs;

	fs = element_pointers_mandatory(dest, el);
	if (!fs)
		fs = element_pointers_bonus(dest, el);
	return (fs);
}
