#include "vector2.h"

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

