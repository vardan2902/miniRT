/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:48:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 19:17:12 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_hit_point(t_hit *hit, float t, t_ray *ray, t_object *object)
{
	t_vector	*position;

	position = get_position_by_type(object);
	if (!position)
		return ;
	hit->t = t;
	hit->position = v_add(*ray->position,
			v_scalar_product(*ray->orientation, t));
	hit->orientation = v_normalize(v_sub(hit->position, *position));
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
				*hit = temp_hit;
				found_hit = true;
			}
		}
		obj = obj->next;
	}
	return (found_hit);
}

static t_object	*find_closest_object(t_list *node, t_ray *ray)
{
	float		closest;
	t_hit		tmp_hit;
	t_object	*closest_obj;

	closest = INFINITY;
	closest_obj = NULL;
	while (node)
	{
		if (intersect((t_object *)node->content, ray, &tmp_hit)
			&& tmp_hit.t > EPSILON && tmp_hit.t < closest)
		{
			closest = tmp_hit.t;
			closest_obj = (t_object *)node->content;
		}
		node = node->next;
	}
	return (closest_obj);
}

bool	pick_object_at(int x, int y, t_scene *scene, t_object **object)
{
	t_object	*closest_obj;
	t_ray		*ray;
	t_basis		*basis;

	ray = malloc(sizeof (t_ray));
	if (!ray)
		return (false);
	basis = get_camera_basis(scene->camera);
	generate_ray(ray, get_pixel_ndc(x, y), basis,
		compute_viewport_size(scene->camera->fov));
	ray->position = scene->camera->position;
	closest_obj = find_closest_object(scene->object_list, ray);
	free(basis);
	free_ray(ray);
	if (closest_obj)
		return (*object = closest_obj, true);
	*object = NULL;
	return (false);
}
