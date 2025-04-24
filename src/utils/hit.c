/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:48:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/23 17:19:52 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	*get_position_by_type(t_object *object)
{
	if (object->type == E_SPHERE)
		return (((t_sphere *)object->object)->position);
	if (object->type == E_CYLINDER)
		return (((t_cylinder *)object->object)->position);
	if (object->type == E_PLANE)
		return (((t_plane *)object->object)->position);
	return (NULL);
}

t_vector	*get_orientation_by_type(t_object *object)
{
	if (object->type == E_CYLINDER)
		return (((t_cylinder *)object->object)->orientation);
	if (object->type == E_PLANE)
		return (((t_plane *)object->object)->orientation);
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

bool	find_hit(t_ray ray, t_hit *hit, t_scene *scene)
{
	t_list	*obj;
	t_hit	temp_hit;
	bool	found_hit;

	found_hit = false;
	obj = scene->object_list;
	while (obj)
	{
		if (intersect((t_object *)obj->content, ray, &temp_hit))
		{
			if (temp_hit.t < hit->t)
			{
				*hit = temp_hit;
				found_hit = true;
			}
		}
		obj = obj->next;
	}
	return (found_hit);
}

bool	pick_object_at(int x, int y, t_scene *scene, t_object **object)
{
	t_hit		tmp_hit;
	t_object	*closest_obj;
	t_list		*node;
	float		closest_t;

	closest_obj = NULL;
	node = scene->object_list;
	closest_t = INFINITY;
	while (node)
	{
		t_object *obj = (t_object *)node->content;
		if (intersect(obj, generate_ray(scene->camera, x, y), &tmp_hit)
			&& tmp_hit.t > EPSILON && tmp_hit.t < closest_t)
		{
			closest_t = tmp_hit.t;
			closest_obj = obj;
		}
		node = node->next;
	}
	if (closest_obj)
	{
		*object = closest_obj;
		return (true);
	}
	return (false);
}
