/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:20:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/24 18:49:31 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	intersect_plane(t_ray *ray, t_object *object, t_hit *hit)
{
	t_plane		*plane;
	t_vector	*diff;
	float		denom;
	float		t;

	plane = (t_plane *)object->object;
	denom = v_dot_product(plane->orientation, ray->orientation);
	if (fabs(denom) < 1e-6)
		return (false);
	diff = v_sub(plane->position, ray->position);
	t = v_dot_product(diff, plane->orientation) / denom;
	free(diff);
	if (t < EPSILON)
		return (false);
	set_hit_point(hit, t, ray, object);
	return (true);
}
