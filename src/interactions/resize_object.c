/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:41:38 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 16:41:51 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
}
