/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_scene_destroyer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:20:24 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/13 14:00:45 by corvvs           ###   ########.fr       */
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
		rd_destroy_element(array[i]);
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
		rd_destroy_element(elem);
		elem = temp;
	}
}

void	rd_destroy_scene(t_scene *scene)
{
	rd_destroy_element(scene->ambient);
	rd_destroy_element(scene->camera);
	free_elemarray(scene->lights);
	free_elemarray(scene->objects);
	free_elemarray(scene->spotlights);
	free(scene->recs);
}

void	rd_destroy_temp_scene_succ(t_temp_scene *temp_scene)
{
	free(temp_scene->content);
	rd_free_strarray(&temp_scene->lines);
	rd_free_strarray(&temp_scene->words);
	ft_bzero(temp_scene, sizeof(t_temp_scene));
}

void	rd_destroy_temp_scene_fail(t_temp_scene *temp_scene)
{
	rd_destroy_element(temp_scene->el);
	rd_destroy_element(temp_scene->ambient);
	rd_destroy_element(temp_scene->camera);
	free_elemlist(temp_scene->light_list);
	free_elemlist(temp_scene->object_list);
	free_elemlist(temp_scene->spotlight_list);
	rd_destroy_temp_scene_succ(temp_scene);
}
