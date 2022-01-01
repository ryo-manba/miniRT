#include "minirt.h"

#define COLOR_MAX 255
#define SHIFT_T 24
#define SHIFT_R 16
#define SHIFT_G 8
#define SHIFT_B 0

int rt_create_trgb(int t, int r, int g, int b)
{
	return (t << SHIFT_T | r << SHIFT_R | g << SHIFT_G | b);
}

t_vec3	rt_color_at(
	t_img *image,
	int x, int y
)
{
	t_vec3	cv;

	const unsigned int color = mr_mlx_pixel_get(image, x, y);
	cv.x = ((color >> 16) & 0xff) / 255.0;
	cv.y = ((color >> 8) & 0xff) / 255.0;
	cv.z = (color & 0xff) / 255.0;
	return (cv);
}

double	rt_grayscale_color_at(
	t_img *image,
	int x, int y
)
{
	const unsigned int color = mr_mlx_pixel_get(image, x, y);
	return ((color & 0xff) / 255.0);
}

t_vec3	rt_element_color(double u, double v, t_element *el)
{
	const t_img	*texture = el->texture;

	if (!texture)
		return (el->color);
	double jd = fmod(u * texture->width + 100000 * texture->width, texture->width);
	double id = fmod(v * texture->height + 100000 * texture->height, texture->height);
	int ji = jd;
	int ii = id;
	return (rt_color_at((t_img *)texture, ji, ii));
}

