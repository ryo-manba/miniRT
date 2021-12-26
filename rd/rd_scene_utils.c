/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_scene_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:20:24 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/25 16:23:14 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static void	free_elemarray(t_element **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i += 1;
	}
	free(array);
}

static void	free_elemlist(t_element *elem)
{
	t_element	*temp;

	while (elem)
	{
		temp = elem->next;
		free(elem);
		elem = temp;
	}
}

void	rd_destroy_scene(t_scene *scene)
{
	free(scene->ambient);
	free(scene->camera);
	free_elemarray(scene->lights);
	free_elemarray(scene->objects);
}

void	rd_destroy_temp_scene(t_temp_scene *temp_scene)
{
	free(temp_scene->ambient);
	free(temp_scene->camera);
	free_elemlist(temp_scene->light_list);
	free_elemlist(temp_scene->object_list);
	free_elemlist(temp_scene->spotlight_list);
}
