/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:27:43 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/26 20:10:12 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	set_new_pos(t_mlx *mlx, t_vector right, float dx, float dy)
{
	t_vector	right_scalar;
	t_vector	new_pos;
	t_vector	*position;
	t_vector	up_scalar;
	t_vector	up;

	up = get_cam_up(mlx, right);
	position = get_position_by_type(mlx->mouse_state.hit_object);
	right_scalar = v_scalar_product(right, -dx * 0.03f);
	new_pos = v_add(*position, right_scalar);
	up_scalar = v_scalar_product(up, -dy * 0.03f);
	new_pos = v_add(new_pos, up_scalar);
	*position = new_pos;
}

void	translate_object(t_mlx *mlx, float dx, float dy)
{
	t_vector	right;

	right = get_cam_right(mlx);
	set_new_pos(mlx, right, dx, dy);
}
