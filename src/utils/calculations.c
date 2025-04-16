/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:18:41 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/15 20:25:11 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	calculate_coefficients(t_coefficients *coefficients,
			t_ray ray, t_vector *position, float radius)
{
	t_vector	*oc;

	oc = v_sub(ray.position, position);
	coefficients->a = v_dot_product(ray.orientation, ray.orientation);
	coefficients->b = 2.0 * v_dot_product(oc, ray.orientation);
	coefficients->c = v_dot_product(oc, oc) - radius * radius;
}

float	calculate_discriminant(float a, float b, float c)
{
	float	discriminant;

	discriminant = b * b - 4 * a * c;
	return (discriminant);
}

float	calculate_hit(float discriminant, float a, float b)
{
	float	sqrt_d;
	float	x1;
	float	x2;

	sqrt_d = sqrt(discriminant);
	x1 = (-b - sqrt_d) / (2.0f * a);
	x2 = (-b + sqrt_d) / (2.0f * a);
	if (x1 > EPSILON)
		return (x1);
	if (x2 > EPSILON)
		return (x2);
	return (-1);
}
