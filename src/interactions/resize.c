/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:29:15 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/26 19:29:34 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
	{
		t_sphere *sphere = (t_sphere *)hit_object->object;
		float new_diameter = sphere->diameter + delta;
		if (new_diameter >= MIN_DIAMETER && new_diameter <= MAX_DIAMETER)
			sphere->diameter = new_diameter;
	}
	else if (hit_object->type == E_CYLINDER)
	{
		t_cylinder *cylinder = (t_cylinder *)hit_object->object;
		float new_diameter = cylinder->diameter + delta;
		float new_height = cylinder->height + delta * 2;

		if (new_diameter >= MIN_DIAMETER && new_diameter <= MAX_DIAMETER &&
			new_height >= MIN_HEIGHT && new_height <= MAX_HEIGHT)
		{
			cylinder->diameter = new_diameter;
			cylinder->height = new_height;
		}
	}
}
