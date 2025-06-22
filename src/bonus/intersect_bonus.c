/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:49:42 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 16:50:25 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

bool	intersect(t_object *object, t_ray *ray, t_hit *hit)
{
	if (object->type == E_SPHERE)
		return (intersect_sphere(ray, object, hit));
	if (object->type == E_PLANE)
		return (intersect_plane(ray, object, hit));
	if (object->type == E_CYLINDER)
		return (intersect_cylinder(ray, object, hit));
	if (object->type == E_CONE)
		return (intersect_cone(ray, object, hit));
	return (false);
}
