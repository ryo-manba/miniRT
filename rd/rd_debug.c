/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:13 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/14 21:55:12 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

void	debug_rd_print_words(char *words[])
{
	while (*words)
	{
		printf("[%s] ", *words);
		words += 1;
	}
	printf("\n");
}

void	debug_rd_print_vector(t_vec3 *vec)
{
	printf("(%f, %f, %f)\n", vec->x, vec->y, vec->z);
}

void	debug_rd_print_element(t_element *element)
{
	printf("{");
	printf(" position: ");
	debug_rd_print_vector(&element->position);
	printf(" direction: ");
	debug_rd_print_vector(&element->direction);
	printf(" ratio: %f", element->ratio);
	printf(" radius: %f", element->radius);
	printf(" diameter: %f", element->diameter);
	printf(" height: %f", element->height);
	printf(" color: ");
	debug_rd_print_vector(&element->color);
	printf("}\n");
}

void	debug_rd_print_element_list(t_element *element)
{
	t_element	*temp;

	temp = element;
	printf("[");
	while (temp)
	{
		printf("%d:%p ", temp->etype, temp);
		temp = temp->next;
	}
	printf("]");
}

void	debug_rd_print_element_array(t_element **element)
{
	size_t	i;

	i = 0;
	printf("[");
	while (element[i])
	{
		printf("%d:%p ", element[i]->etype, element[i]);
		i += 1;
	}
	printf("]");
}
