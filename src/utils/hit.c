/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:48:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 16:11:24 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_vector	*get_position_by_type(t_object *object)
{
	if (object->type == E_SPHERE)
		return (((t_sphere *)object->object)->position);
	if (object->type == E_CYLINDER)
		return (((t_cylinder *)object->object)->position);
	return (NULL);
}

void	set_hit_point(t_hit *hit, float t, t_ray ray, t_object *object)
{
	t_vector	*position;

	position = get_position_by_type(object);
	hit->t = t;
	hit->position = v_add(ray.position, v_scalar_product(ray.orientation, t));
	hit->orientation = v_normalize(v_sub(hit->position, position));
	hit->object = object;
}
