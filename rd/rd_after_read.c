/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_after_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 22:40:17 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/11 22:41:34 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static bool	list_to_array(t_element *list, size_t *n_ptr, t_element ***array)
{
	t_element	*el;
	size_t		i;

	el = list;
	while (el)
	{
		*n_ptr += 1;
		el = el->next;
	}
	*array = (t_element **)ft_calloc(*n_ptr + 1, sizeof(t_element *));
	if (!*array)
		return (false);
	i = 0;
	el = list;
	while (el)
	{
		(*array)[i] = el;
		i += 1;
		el = el->next;
	}
	return (true);
}

bool	rd_after_read(
	t_temp_scene *temp_scene, t_scene *scene)
{
	if (!temp_scene->ambient)
		return (rd_print_error("ambient not found", temp_scene));
	if (!temp_scene->camera)
		return (rd_print_error("camera not found", temp_scene));
	if (!temp_scene->light_list)
		return (rd_print_error("light not found", temp_scene));
	ft_bzero(scene, sizeof(t_scene));
	list_to_array(temp_scene->light_list,
		&scene->n_lights, &scene->lights);
	list_to_array(temp_scene->object_list,
		&scene->n_objects, &scene->objects);
	list_to_array(temp_scene->spotlight_list,
		&scene->n_spotlights, &scene->spotlights);
	scene->ambient = temp_scene->ambient;
	scene->camera = temp_scene->camera;
	rd_destroy_temp_scene_succ(temp_scene);
	return (true);
}
