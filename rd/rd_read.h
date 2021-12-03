/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_read.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:35:57 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/03 16:55:03 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RD_READ_H
# define RD_READ_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../mr_vec3.h"
# include "../libft/libft.h"
# include "mr_read.h"

# define RD_EPSILON 1e-7

# define RD_ID_AMBIENT	"A"
# define RD_ID_CAMERA	"C"
# define RD_ID_LIGHT	"L"
# define RD_ID_SPHERE	"sp"
# define RD_ID_PLANE	"pl"
# define RD_ID_CYLINDER	"cy"

typedef struct s_temp_scene
{
	t_element	*ambient;
	t_element	*camera;
	t_element	*light_list;
	t_element	*object_list;
}	t_temp_scene;

typedef union u_ull_double
{
	unsigned long long	ull;
	double				dbl;
}	t_ull_double;

typedef bool	(*t_element_info_predicate)(const char*);
typedef bool	(*t_element_info_extractor)(const char*, void*);

bool			rd_print_error(const char *error);
char			*rd_read_file_content(const char *filename);
void			debug_rd_print_words(char **words);
void			debug_rd_print_element(t_element *element);
void			debug_rd_print_element_list(t_element *element);
void			debug_rd_print_element_array(t_element **element);

t_element_type	rd_detect_element_type(const char **words);

bool			rd_is_positive_real(const char *str);
bool			rd_is_ratio(const char *str);
bool			rd_is_fov_angle(const char *str);
bool			rd_is_vector(const char *str);
bool			rd_is_unit_vector(const char *str);
bool			rd_is_color_vector(const char *str);

void			rd_vectorize(const char *str, t_vec3 *vector);
void			rd_free_strarray(char **strs);

double			rd_str_to_double(const char *str);
bool			rd_is_finite(const double val);
double			rd_nan(void);

t_element		*rd_extract_element(t_element_type etype,
					const char **words);

void			rd_destroy_temp_scene(t_temp_scene *temp_scene);


#endif
