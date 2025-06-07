/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:58 by vapetros          #+#    #+#             */
/*   Updated: 2025/05/18 17:49:50 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	v_length(t_vector v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	init_zero_vec(void)
{
	t_vector	zero_vec;

	zero_vec.x = 0.0f;
	zero_vec.y = 0.0f;
	zero_vec.z = 0.0f;
	return (zero_vec);
}

t_vector	v_normalize(t_vector v)
{
	float		len;
	t_vector	new_vec;

	len = v_length(v);
	if (len == 0.0f || len < 1e-6f)
		return (init_zero_vec());
	new_vec.x = v.x / len;
	new_vec.y = v.y / len;
	new_vec.z = v.z / len;
	return (new_vec);
}

void	assign_vector(t_vector src, t_vector *dst)
{
	dst->x = src.x;
	dst->y = src.y;
	dst->z = src.z;
}

t_vector	v_rotate(t_vector v, t_vector axis, float angle)
{
	t_vector	normalized_axis;
	t_vector	terms_total;
	float		cos_theta;
	float		sin_theta;

	normalized_axis = v_normalize(axis);
	sin_theta = sinf(angle);
	cos_theta = cosf(angle);
	terms_total = v_add(v_scalar_product(v, cos_theta), v_scalar_product(
				v_cross_product(normalized_axis, v), sin_theta));
	return (v_add(terms_total, v_scalar_product(normalized_axis,
				v_dot_product(normalized_axis, v) * (1.0f - cos_theta))));
}

t_vector v_reflect(t_vector inverted_light_dir, t_vector normal)
{
    return v_sub(inverted_light_dir, v_scalar_product(normal, 2.0f * v_dot_product(normal, inverted_light_dir)));
}