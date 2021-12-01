/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_read.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:35:57 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/01 12:23:14 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_READ_H
# define RT_READ_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include "../mr_vec3.h"
# include "../libft/libft.h"

# define RD_EPSILON 1e-7

# define RD_ID_AMBIENT	"A"
# define RD_ID_CAMERA	"C"
# define RD_ID_LIGHT	"L"
# define RD_ID_SPHERE	"sp"
# define RD_ID_PLANE	"pl"
# define RD_ID_CYLINDER	"cy"

typedef enum e_element_type
{
	RD_ET_DUMMY,
	RD_ET_AMBIENT,
	RD_ET_CAMERA,
	RD_ET_LIGHT,
	RD_ET_SPHERE,
	RD_ET_PLANE,
	RD_ET_CYLINDER,
	RD_ET_UNEXPECTED,
}	t_element_type;

typedef struct s_element
{
	t_element_type	etype;
	t_vec3			position;
	t_vec3			direction;
	t_vec3			color;
	double			ratio;
	double			radius;
	double			diameter;
	double			height;
	double			fov;
}	t_element;

typedef union u_ull_double
{
	unsigned long long	ull;
	double				dbl;
}	t_ull_double;

typedef bool (*t_element_info_predicate)(const char*);
typedef bool (*t_element_info_extractor)(const char*, void*);

char	*rd_read_file_content(const char *filename);
void	debug_rd_print_words(char **words);
void	debug_rd_print_element(t_element *element);

t_element_type	rd_detect_element_type(const char** words);

bool	rd_is_positive_real(const char *str);
bool	rd_is_ratio(const char *str);
bool	rd_is_fov_angle(const char *str);
bool	rd_is_vector(const char *str);
bool	rd_is_unit_vector(const char *str);
bool	rd_is_color_vector(const char *str);

void	rd_vectorize(const char* str, t_vec3* vector);
void	rd_free_strarray(char **strs);

double	rd_str_to_double(const char *str);
bool	rd_is_finite(const double val);
double	rd_inf(bool positive);
double	rd_nan(void);

t_element	*rd_extract_element(t_element_type etype,
				const char **words);

#endif
