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
void	mr_mlx_pixel_put(t_img *img, int x, int y, int color);
int		mr_exit_window(t_info *info);

/* color */
int rt_create_trgb(int t, int r, int g, int b);
int	rt_get_trgb(int trgb, int shift);
int	rt_add_shade(double distance, int color);
int	rt_get_opposite(int color);

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
	const t_vec3 *light_p,
	const t_vec3 *light_color,
	const t_ray *ray);

t_vec3	rt_specular(
	const t_hit_record *rec,
	const t_vec3 *light,
	const t_vec3 *light_color,
	const t_ray *ray);

bool	rt_is_shadow(
	const t_hit_record *actual,
	const t_scene *scene,
	t_hit_record *recs,
	const t_vec3 *light_pos);

/* debug */
void	vec3_debug(t_vec3 *vec);

#endif
