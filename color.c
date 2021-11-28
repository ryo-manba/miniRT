#include "minirt.h"

#define COLOR_MAX 255
#define SHIFT_T 24
#define SHIFT_R 16
#define SHIFT_G 8
#define SHIFT_B 0

// 0xTTRRGGBB
// t = transparency(透明性)
int create_trgb(int t, int r, int g, int b)
{
	return (t << SHIFT_T | r << SHIFT_R | g << SHIFT_G | b);
}

int	get_trgb(int trgb, int shift)
{
	return (trgb & (0xFF << shift));
}

/*
static void debug(int color)
{
	const int	t = get_trgb(color, SHIFT_T);
	const int	r = get_trgb(color, SHIFT_R);
	const int	g = get_trgb(color, SHIFT_G);
	const int	b = get_trgb(color, SHIFT_B);

	printf("t = [%d]\nr = [%d]\ng = [%d]\nb = [%d]\n",\
			t>>SHIFT_T, r>>SHIFT_R, g>>SHIFT_G, b);
}
*/

// distanceが0から1に近づくに連れて暗くなる
int	add_shade(double distance, int color)
{
	const int	t = get_trgb(color, SHIFT_T) / (1 << SHIFT_T);
	const int	r = (get_trgb(color, SHIFT_R) / (1 << SHIFT_R))* (1.0f - distance);
	const int	g = (get_trgb(color, SHIFT_G) / (1 << SHIFT_G))* (1.0f - distance);
	const int	b = (get_trgb(color, SHIFT_B) / (1 << SHIFT_B))* (1.0f - distance);

	return (create_trgb(t, r, g, b));
}

// 色を反転させる
int	get_opposite(int color)
{
	const unsigned int	t = get_trgb(color, SHIFT_T) / (1 << SHIFT_T);
	const unsigned int	r = COLOR_MAX - (get_trgb(color, SHIFT_R) / (1 << SHIFT_R));
	const unsigned int	g = COLOR_MAX - (get_trgb(color, SHIFT_G) / (1 << SHIFT_G));
	const unsigned int	b = COLOR_MAX - (get_trgb(color, SHIFT_B) / (1 << SHIFT_B));

	return (create_trgb(t, r, g, b));
}
