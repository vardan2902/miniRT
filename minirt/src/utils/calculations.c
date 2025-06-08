/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:18:41 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/08 19:19:21 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	calculate_coefficients(t_coefficients *coefficients,
			t_ray *ray, t_vector *position, float radius)
{
	t_vector	oc;

	oc = v_sub(*ray->position, *position);
	coefficients->a = v_dot_product(*ray->orientation, *ray->orientation);
	coefficients->b = 2.0 * v_dot_product(oc, *ray->orientation);
	coefficients->c = v_dot_product(oc, oc) - radius * radius;
}

float	calculate_discriminant(float a, float b, float c)
{
	float	discriminant;

	discriminant = powf(b, 2) - 4 * a * c;
	return (discriminant);
}

t_roots	calculate_hit(float discriminant, float a, float b)
{
	float	sqrt_d;
	t_roots	roots;

	sqrt_d = sqrt(discriminant);
	roots.t1 = (-b - sqrt_d) / (2.0f * a);
	roots.t2 = (-b + sqrt_d) / (2.0f * a);
	return (roots);
}
