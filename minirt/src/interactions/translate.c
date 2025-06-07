/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:27:43 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/07 18:05:39 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	set_new_pos(t_mlx *mlx, t_vector right, float dx, float dy)
{
	t_vector	right_scalar;
	t_vector	up_scalar;
	t_vector	new_pos;
	t_vector	*position;
	float		speed;

	position = get_position_by_type(mlx->mouse_state.hit_object);
	speed = v_length(v_sub(*position, *mlx->scene->camera->position)) * 0.001f;
	right_scalar = v_scalar_product(right, -dx * speed);
	up_scalar = v_scalar_product(get_cam_up(mlx, right), -dy * speed);
	new_pos = v_add(*position, right_scalar);
	new_pos = v_add(new_pos, up_scalar);
	*position = new_pos;
}

void	translate_object(t_mlx *mlx, float dx, float dy)
{
	t_vector	right;

	right = get_cam_right(mlx);
	set_new_pos(mlx, right, dx, dy);
}
