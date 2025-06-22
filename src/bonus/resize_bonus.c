/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:38:50 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 19:54:00 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_cone_height(t_cone *cone, float delta)
{
	float	new_height;
	float	min_height;
	float	max_height;

	new_height = cone->height + delta * 2;
	min_height = fmin(MIN_HEIGHT, cone->initial_height);
	max_height = fmax(MAX_HEIGHT, cone->initial_height);
	if (new_height >= min_height && new_height <= max_height)
		cone->height = new_height;
	else if (new_height < min_height)
		cone->height = min_height;
	else if (new_height > max_height)
		cone->height = max_height;
}

void	resize_cone_diameter(t_cone *cone, float delta)
{
	float	new_diameter;
	float	min_diameter;
	float	max_diameter;

	new_diameter = cone->diameter + delta;
	min_diameter = fmin(MIN_DIAMETER, cone->initial_diameter);
	max_diameter = fmax(MAX_DIAMETER, cone->initial_diameter);
	if (new_diameter >= min_diameter && new_diameter <= max_diameter)
		cone->diameter = new_diameter;
	else if (new_diameter < min_diameter)
		cone->diameter = min_diameter;
	else if (new_diameter > max_diameter)
		cone->diameter = max_diameter;
}

static void	resize_cone(t_object *hit_object, float delta)
{
	t_cone	*cone;

	cone = (t_cone *)hit_object->object;
	resize_cone_diameter(cone, delta);
	resize_cone_height(cone, delta);
}

void	resize_object(t_mlx *mlx, bool is_plus)
{
	t_object	*hit_object;
	t_vector	*cam_pos;
	t_vector	*obj_pos;
	float		delta;

	hit_object = mlx->hit_object;
	cam_pos = mlx->scene->camera->position;
	obj_pos = get_position_by_type(hit_object);
	delta = v_length(v_sub(*obj_pos, *cam_pos)) * BASE_SCALE;
	if (!is_plus)
		delta = -delta;
	if (hit_object->type == E_SPHERE)
		return (resize_sphere(hit_object, delta));
	else if (hit_object->type == E_CYLINDER)
		return (resize_cylinder(hit_object, delta));
	else if (hit_object->type == E_CONE)
		return (resize_cone(hit_object, delta));
}
