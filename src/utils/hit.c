/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:48:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/28 19:40:28 by ysaroyan         ###   ########.fr       */
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

void	set_hit_point(t_hit *hit, float t, t_ray *ray, t_object *object)
{
	t_vector	*position;
	t_vector	*temp;

	position = get_position_by_type(object);
	if (!position)
		return ;
	hit->t = t;
	temp = v_scalar_product(ray->orientation, t);
	hit->position = v_add(ray->position, temp);
	free(temp);
	temp = v_sub(hit->position, position);
	hit->orientation = v_normalize(temp);
	free(temp);
	hit->object = object;
}

bool	find_hit(t_ray *ray, t_hit *hit, t_scene *scene)
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
				free_hit(hit);
				*hit = temp_hit;
				found_hit = true;
			}
			else
				free_hit(&temp_hit);
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
	t_ray		*ray;
	float		closest_t;

	closest_obj = NULL;
	node = scene->object_list;
	closest_t = INFINITY;
	while (node)
	{
		ray = generate_ray(scene->camera, x, y);
		if (intersect((t_object *)node->content, ray, &tmp_hit)
			&& tmp_hit.t > EPSILON && tmp_hit.t < closest_t)
		{
			closest_t = tmp_hit.t;
			closest_obj = (t_object *)node->content;
			free_hit(&tmp_hit);
		}
		free_ray(ray);
		node = node->next;
	}
	if (closest_obj)
		return (*object = closest_obj, true);
	return (false);
}
