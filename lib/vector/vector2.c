#include "vector2.h"
#include <math.h>

t_vector2 *v_add(t_vector2 *vec1, t_vector2 vec2)
{
	vec1->x += vec2.x;
	vec1->y += vec2.y;
	return vec1;
}

void v_mul_scal(t_vector2 *vec, float scal)
{
	vec->x *= scal;
	vec->y *= scal;
}

double v_dist(t_vector2 vec1, t_vector2 vec2)
{
	double dx = vec2.x - vec1.x;
	double dy = vec2.y - vec1.y;

	return sqrt(dx * dx + dy * dy);
}

