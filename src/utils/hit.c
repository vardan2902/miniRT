/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:48:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 15:20:31 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_hit_point(t_hit *hit, float t, t_ray ray, t_object *object)
{
	t_vector	*position;
	t_sphere	*obj;

	obj = (t_sphere *)object->object;
	position = obj->position;
	hit->t = t;
	hit->position = v_add(ray.position, v_scalar_product(ray.orientation, t));
	hit->orientation = v_normalize(v_sub(hit->position, position));
	hit->object = object;
}
