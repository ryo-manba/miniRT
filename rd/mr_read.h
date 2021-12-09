/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_read.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:45:06 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/08 20:05:11 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MR_READ_H
# define MR_READ_H

# include <stdlib.h>
# include <stdbool.h>
# include "../common/mr_common.h"
# include "../mr_vec3.h"

bool	rd_read_scene(const char *filename, t_scene *scene);
void	rd_destroy_scene(t_scene *scene);
double	rd_inf(bool positive);

#endif
