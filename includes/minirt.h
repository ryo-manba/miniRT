#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
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
# else
#  define KEY_ESC 53
# endif

/* colorcode */
# define BLACK 0x000000
# define WHITE 0xffffff

/* hooks */
void			mr_mlx_pixel_put(t_img *img, int x, int y, int color);
unsigned int	mr_mlx_pixel_get(t_img *img, int x, int y);
int				mr_exit_window(t_info *info);

int rt_create_trgb(int t, int r, int g, int b);
t_vec3	rt_color_at(t_img *image, int x, int y);
double	rt_grayscale_color_at(t_img *image, int x, int y);
t_vec3	rt_element_color(double u, double v, t_element *el);

t_vec3	rt_hit_point(double t, const t_ray *ray);
void	rt_after_hit(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec);

t_vec3	rt_orient_vector(t_vec3 *v, t_vec3 *orient);


bool	rt_hit_object(
	t_element *el,
	const t_ray *ray,
	t_hit_record *rec
);

/* refraction */
t_vec3 rt_ambient(
	const double ratio,
	const t_vec3 *ambient_color,
	const t_vec3 *obj_color);

t_vec3	rt_diffuse(
	const t_hit_record *rec,
	const t_element *light,
	const t_vec3 *light_color);

t_vec3	rt_specular(
	const t_hit_record *rec,
	const t_vec3 *light,
	const t_vec3 *light_color,
	const t_ray *ray);

bool	rt_is_shadow(
	const t_hit_record *actual,
	const t_element *light,
	t_scene *scene,
	t_ray *ray);

/* debug */
void	vec3_debug(t_vec3 *vec);

#endif
