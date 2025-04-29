/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:58 by vapetros          #+#    #+#             */
/*   Updated: 2025/04/28 19:35:04 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	v_length(t_vector *a)
{
	return (v_dot_product(a, a));
}

t_vector	*v_normalize(t_vector *a)
{
	return (v_scalar_product(a, 1.0f / v_length(a)));
}

static t_vector	*get_terms_total(t_vector *v, t_vector *axis,
		float angle, float cos_theta)
{
	t_vector	*term1;
	t_vector	*term2;
	t_vector	*term2_cross;
	t_vector	*total;
	float		sin_theta;

	sin_theta = sinf(angle);
	term2_cross = v_cross_product(axis, v);
	term2 = v_scalar_product(term2_cross, sin_theta);
	term1 = v_scalar_product(v, cos_theta);
	total = v_add(term1, term2);
	free(term1);
	free(term2);
	free(term2_cross);
	return (total);
}

t_vector	*v_rotate(t_vector *v, t_vector *axis, float angle)
{
	t_vector	*normalized_axis;
	t_vector	*term3;
	t_vector	*terms_total;
	t_vector	*result;
	float		cos_theta;

	normalized_axis = v_normalize(axis);
	cos_theta = cosf(angle);
	terms_total = get_terms_total(v, normalized_axis, angle, cos_theta);
	term3 = v_scalar_product(normalized_axis,
			v_dot_product(normalized_axis, v) * (1.0f - cos_theta));
	result = v_add(terms_total, term3);
	free(normalized_axis);
	free(term3);
	free(terms_total);
	return (result);
}
