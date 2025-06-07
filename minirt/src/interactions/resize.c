/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:29:15 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/07 18:03:49 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	resize_sphere(t_object *hit_object, float delta)
{
	t_sphere	*sphere;
	float		new_diameter;
	float		min;
	float		max;

	sphere = (t_sphere *)hit_object->object;
	min = fmin(MIN_DIAMETER, sphere->initial_diameter);
	max = fmax(MAX_DIAMETER, sphere->initial_diameter);
	new_diameter = sphere->diameter + delta;
	if (new_diameter >= min && new_diameter <= max)
		sphere->diameter = new_diameter;
	else if (new_diameter < min)
		sphere->diameter = min;
	else if (new_diameter > max)
		sphere->diameter = max;
}

static void	resize_cylinder_height(t_cylinder *cylinder, float delta)
{
	float	new_height;
	float	min_height;
	float	max_height;

	new_height = cylinder->height + delta * 2;
	min_height = fmin(MIN_HEIGHT, cylinder->initial_height);
	max_height = fmax(MAX_HEIGHT, cylinder->initial_height);
	if (new_height >= min_height && new_height <= max_height)
		cylinder->height = new_height;
	else if (new_height < min_height)
		cylinder->height = min_height;
	else if (new_height > max_height)
		cylinder->height = max_height;
}

static void	resize_cylinder_diameter(t_cylinder *cylinder, float delta)
{
	float	new_diameter;
	float	min_diameter;
	float	max_diameter;

	new_diameter = cylinder->diameter + delta;
	min_diameter = fmin(MIN_DIAMETER, cylinder->initial_diameter);
	max_diameter = fmax(MAX_DIAMETER, cylinder->initial_diameter);
	if (new_diameter >= min_diameter && new_diameter <= max_diameter)
		cylinder->diameter = new_diameter;
	else if (new_diameter < min_diameter)
		cylinder->diameter = min_diameter;
	else if (new_diameter > max_diameter)
		cylinder->diameter = max_diameter;
}

static void	resize_cylinder(t_object *hit_object, float delta)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)hit_object->object;
	resize_cylinder_diameter(cylinder, delta);
	resize_cylinder_height(cylinder, delta);
}

void	resize_object(t_mlx *mlx, bool is_plus)
{
	t_object	*hit_object;
	t_vector	*cam_pos;
	t_vector	*obj_pos;
	float		delta;

	hit_object = mlx->mouse_state.hit_object;
	cam_pos = mlx->scene->camera->position;
	obj_pos = get_position_by_type(hit_object);
	delta = v_length(v_sub(*obj_pos, *cam_pos)) * BASE_SCALE;
	if (!is_plus)
		delta = -delta;
	if (hit_object->type == E_SPHERE)
		return (resize_sphere(hit_object, delta));
	else if (hit_object->type == E_CYLINDER)
		return (resize_cylinder(hit_object, delta));
}
