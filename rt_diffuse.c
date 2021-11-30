#include "minirt.h"
#include "mr_vec3.h"

#define PI acos(-1)

double	rt_random_double(double min, double max)
{
	const double	random = rand() / (RAND_MAX + 1.0); // [0, 1)

	if (min == max)
		return (random);
	else
		return (min + (max - min) * random);
}

t_vec3	rt_random(double min, double max)
{
	t_vec3	random;

	mr_vec3_init(&random, \
			  rt_random_double(min, max), \
			  rt_random_double(min, max), \
			  rt_random_double(min, max));
	return (random);
}

t_vec3	rt_random_in_unit_sphere()
{
	while (true)
	{
		t_vec3	p = rt_random(-1, 1);
		if (mr_vec3_length_squared(p) >= 1) // 単位球面よりも大きかった場合
		{
			continue;
		}
		return (p);
	}
}

t_vec3	rt_random_unit_vector()
{
	double	a = rt_random_double(0, 2 * PI);
	double	z = rt_random_double(-1, 1);
	double	r = sqrt(1 - z * z);
	t_vec3	vec;

	mr_vec3_init(&vec, r * cos(a), r * sin(a), z);
	return (vec);
}
