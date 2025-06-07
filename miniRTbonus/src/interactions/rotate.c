/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:28:16 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 13:47:43 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_object(t_mlx *mlx, float dx, float dy)
{
	t_vector	*orientation;
	t_vector	right;
	t_vector	up;
	t_vector	rotated;

	right = get_cam_right(mlx);
	up = get_cam_up(mlx, right);
	orientation = get_orientation_by_type(mlx->mouse_state.hit_object);
	if (dx != 0)
		rotated = v_rotate(*orientation, up, dx * 0.1f);
	if (dy != 0)
		rotated = v_rotate(*orientation, right, dy * 0.1f);
	*orientation = v_normalize(rotated);
}
