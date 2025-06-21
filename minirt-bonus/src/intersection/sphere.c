/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:40:24 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 19:09:40 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	intersect_sphere(t_ray *ray, t_object *object, t_hit *hit)
{
	t_sphere		*sphere;
	t_coefficients	coeff;
	float			discriminant;
	t_roots			roots;
	bool			inside_object;

	inside_object = false;
	sphere = (t_sphere *)object->object;
	calculate_coefficients(&coeff, ray, sphere->position, sphere->diameter / 2);
	discriminant = calculate_discriminant(coeff.a, coeff.b, coeff.c);
	if (discriminant < 0)
		return (false);
	roots = calculate_hit(discriminant, coeff.a, coeff.b);
	if (roots.t1 > EPSILON)
		set_hit_point(hit, roots.t1, ray, object);
	else if (roots.t2 > EPSILON)
	{
		set_hit_point(hit, roots.t2, ray, object);
		hit->orientation = v_scalar_product(hit->orientation, -1.0f);
	}
	else
		return (false);
	return (true);
}
