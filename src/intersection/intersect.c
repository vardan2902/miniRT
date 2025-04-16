/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:36:08 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/15 18:39:07 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	intersect(t_object *object, t_ray ray, t_hit *hit)
{
	if (object->type == E_SPHERE)
		return (intersect_sphere(ray, object, hit));
	if (object->type == E_PLANE)
		return (intersect_plane(ray, object, hit));
	return (false);
}
