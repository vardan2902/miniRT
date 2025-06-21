/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:48:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/21 17:40:56 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_hit_point(t_hit *hit, float t, t_ray *ray, t_object *object)
{
	t_vector	*position;
	t_vector	pos;
	t_vector	orient;

	position = get_position_by_type(object);
	if (!position)
		return ;
	hit->t = t;
	pos = v_add(*ray->position, v_scalar_product(*ray->orientation, t));
	hit->position = pos;
	orient = v_normalize(v_sub(hit->position, *position));
	hit->orientation = orient;
	hit->object = object;
}

bool	find_hit(t_ray *ray, t_hit *hit, t_scene *scene)
{
	t_list	*obj;
	t_hit	temp_hit;
	bool	found_hit;

	found_hit = false;
	obj = scene->object_list;
	temp_hit.t = FLT_MAX;
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

void	find_closest_obj(t_list *object_list, t_ray *ray,
		t_object **closest_obj)
{
	t_list		*node;
	t_hit		tmp_hit;
	float		closest_t;

	closest_t = INFINITY;
	tmp_hit.t = FLT_MAX;
	node = object_list;
	while (node)
	{
		if (intersect((t_object *)node->content, ray, &tmp_hit)
			&& tmp_hit.t > EPSILON && tmp_hit.t < closest_t)
		{
			closest_t = tmp_hit.t;
			*closest_obj = (t_object *)node->content;
		}
		node = node->next;
	}
}

bool	pick_object_at(int x, int y, t_scene *scene,
			t_object **object)
{
	t_object	*closest_obj;
	t_ray		*ray;
	t_basis		*basis;

	closest_obj = NULL;
	ray = malloc(sizeof (t_ray));
	if (!ray)
		return (false);
	basis = get_camera_basis(scene->camera);
	generate_ray(ray, get_pixel_ndc(x, y), basis,
		compute_viewport_size(scene->camera->fov));
	ray->position = scene->camera->position;
	find_closest_obj(scene->object_list, ray, &closest_obj);
	free(basis);
	free_ray(ray);
	if (closest_obj)
		return (*object = closest_obj, true);
	return (*object = NULL, false);
}
