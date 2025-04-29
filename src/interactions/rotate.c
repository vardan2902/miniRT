/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:28:16 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/26 19:36:22 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_object(t_mlx *mlx, float dx, float dy)
{
	t_vector	*orientation;
	t_vector	*right;
	t_vector	*up;
	t_vector	*rotated;

	right = get_cam_right(mlx);
	up = get_cam_up(mlx, right);
	orientation = get_orientation_by_type(mlx->mouse_state.hit_object);
	if (dx != 0)
		rotated = v_rotate(orientation, up, dx * 0.01f);
	if (dy != 0)
		rotated = v_rotate(orientation, right, dy * 0.01f);
	*orientation = *v_normalize(rotated);
	free(rotated);
	free(up);
	free(right);
}
