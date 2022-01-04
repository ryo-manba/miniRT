/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:07:48 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/03 17:07:49 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mr_read.h"
#include "rd_read.h"

int main()
{
	t_scene	scene;

	if (rd_read_scene("test.rt", &scene) == false)
	{
		return (1);
	}
	printf("ambient:\t");
	debug_rd_print_element_list(scene.ambient);
	printf("\n");
	printf("camera: \t");
	debug_rd_print_element_list(scene.camera);
	printf("\n");
	printf("lights: \t");
	debug_rd_print_element_array(scene.lights);
	printf("\n");
	printf("objects:\t");
	debug_rd_print_element_array(scene.objects);
	printf("\n");

	rd_destroy_scene(&scene);
}
