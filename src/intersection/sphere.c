/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:40:24 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 12:49:27 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	intersect_sphere(t_ray ray, t_object *object, t_hit *hit)
{
	t_sphere		*sphere;
	float			discriminant;
	t_coefficients	coeff;
	float			t;

	sphere = (t_sphere *)object->object;
	calculate_coefficients(&coeff, ray, sphere->position, sphere->diameter / 2);
	discriminant = calculate_discriminant(coeff.a, coeff.b, coeff.c);
	if (discriminant < 0)
		return (false);
	t = calculate_hit(discriminant, coeff.a, coeff.b);
	if (t < 0)
		return (false);
	set_hit_point(hit, t, ray, sphere);
	return (true);
}
