/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:38:27 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/17 20:20:24 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include <pthread.h>
# include <X11/X.h>
# include "libft.h"
# include "mlx.h"
# include "rt_scene.h"
# include "mr_vec3.h"
# include "mr_read.h"
# include "rt_object.h"
# include "rt_texture.h"
# include "rt_coord.h"

/* window size */
//# define WIDTH 500
//# define HEIGHT 500

/* keycode */
# ifdef __linux__
#  define KEY_ESC 65307
#  define EVENT_KEY_PRESS 2
#  define MASK_KEY_PRESS 1L
#  define EVENT_EXPOSE 12
#  define MASK_EXPOSE 32768L
#  define EVENT_CLOSE 17
#  define MASK_CLOSE 131072L
# else
#  define KEY_ESC 65307
#  define EVENT_KEY_PRESS 2
#  define MASK_KEY_PRESS 1L
#  define EVENT_EXPOSE 12
#  define MASK_EXPOSE 32768L
#  define EVENT_CLOSE 17
#  define MASK_CLOSE 131072L
# endif

# ifndef THREADS
#  define THREADS 1
# endif
# ifndef SUBPIXEL
#  define SUBPIXEL 1
# endif

/* colorcode */
# define BLACK 0x000000
# define WHITE 0xffffff

void			mr_bailout(t_info *info, const char *error);

/* hooks */
void			mr_mlx_pixel_put(t_img *img, int x, int y, const t_vec3 v3);
unsigned int	mr_mlx_pixel_get(t_img *img, int x, int y);
int				mr_exit_window(t_info *info);
int				mr_hook_key_press(int key, t_info *info);
bool			mr_read_image_files(t_info *info);
void			mr_destroy_image_files(t_info *info);
int				mr_expose_window(t_info *info);

int				rt_create_trgb(int t, int r, int g, int b);
t_vec3			rt_color_image(double u, double v, t_element *el);
t_vec3			rt_sky_blue(const t_vec3 direction);

void			rt_raytrace(t_info *info, t_scene *scene);

t_vec3			rt_hit_point(double t, const t_ray *ray);
void			rt_after_hit(
					const t_element *el,
					const t_ray *ray,
					t_hit_record *rec);

t_vec3			rt_orient_vector(const t_vec3 *v, const t_vec3 *orient);

bool			rt_hit_object(
					const t_element *el,
					const t_ray *ray,
					t_hit_record *rec);
t_hit_record	*rt_find_actual_hit(t_ray *r, t_subscene *subscene);

/* refrection */
t_vec3			rt_reflect_ray(
					t_ray *r,
					t_subscene *subscene,
					t_hit_record *actual);

t_vec3			rt_color_ambient(
					const double ratio,
					const t_vec3 *ambient_color,
					const t_vec3 *obj_color);

t_vec3			rt_color_diffuse(
					const t_hit_record *rec,
					const t_vec3 *light_incident,
					const t_vec3 *light_color);

t_vec3			rt_color_specular(
					const t_hit_record *rec,
					const t_vec3 *light_incident,
					const t_vec3 *light_color,
					const t_ray *ray);

bool			rt_is_shadowed_from(
					const t_hit_record *actual,
					const t_element *light,
					t_subscene *subscene,
					t_ray *ray);

t_vec3			rt_get_incident_vector(
					const t_hit_record *rec,
					const t_element *light);

double			rt_fmod(double x, double y);
double			rt_floor(double x);

/* debug */
void			vec3_debug(const t_vec3 *vec);

#endif
