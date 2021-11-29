#ifndef MR_VEC3_H
# define MR_VEC3_H

typedef struct vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/* mr_vec3_operator */
t_vec3	mr_vec3_add(t_vec3 u, t_vec3 v);
t_vec3	mr_vec3_sub(t_vec3 u, t_vec3 v);
t_vec3	mr_vec3_mul(t_vec3 u, t_vec3 v);
double	mr_vec3_dot(t_vec3 u, t_vec3 v);
t_vec3	mr_vec3_cross(t_vec3 u, t_vec3 v);

/* mr_vec3_utils */
t_vec3	mr_vec3_mul_double(t_vec3 u, double t);
t_vec3	mr_vec3_div_double(t_vec3 v, double t);
t_vec3	mr_unit_vector(t_vec3 v);
double	mr_vec3_length(t_vec3 v);
double	mr_vec3_length_squared(t_vec3 v);

#endif
