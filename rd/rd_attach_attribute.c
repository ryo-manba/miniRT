/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_attach_attribute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:16:17 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/11 21:20:08 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static bool	attach_texture(
	t_temp_scene *scene, t_element *tail, t_element *el)
{
	if (tail->tex_el)
		return (rd_print_error_cur(&scene->cur,
				"texture already attached"));
	tail->tex_el = el;
	return (true);
}

static bool	attach_bumpmap(
	t_temp_scene *scene, t_element *tail, t_element *el)
{
	if (tail->bump_el)
		return (rd_print_error_cur(&scene->cur,
				"bumpmap already attached"));
	tail->bump_el = el;
	return (true);
}

static bool	attach_material(
	t_temp_scene *scene, t_element *tail, t_element *el)
{
	(void)scene;
	tail->gloss = el->gloss;
	tail->k_diffuse = el->k_diffuse;
	tail->k_specular = el->k_specular;
	rd_destroy_element(el);
	return (true);
}

bool	rd_attach_attribute(
	t_temp_scene *scene, t_element **list, t_element *el)
{
	t_element	*tail;

	tail = *list;
	if (!tail)
		return (rd_print_error_cur(&scene->cur, "no object to attach"));
	while (tail->next)
		tail = tail->next;
	if (el->etype == RD_ET_TEXTURE || el->etype == RD_ET_CHECKER)
	{
		return (attach_texture(scene, tail, el));
	}
	else if (el->etype == RD_ET_BUMPMAP)
	{
		return (attach_bumpmap(scene, tail, el));
	}
	else if (el->etype == RD_ET_MATERIAL)
	{
		return (attach_material(scene, tail, el));
	}
	return (true);
}
