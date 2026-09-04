#ifndef VECTOR2_H
#define VECTOR2_H
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector2;

t_vector2 *v_add(t_vector2 *vec1, t_vector2 vec2);
void v_mul_scal(t_vector2 *vec, float scal);
double v_dist(t_vector2 vec1, t_vector2 vec2);

#endif // !VECTOR2_H
