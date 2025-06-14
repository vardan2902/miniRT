/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:28:16 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 19:57:34 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_object(t_mlx *mlx, int key)
{
	t_vector	*orientation;
	t_vector	rotated;
	float		angle;

	rotated = (t_vector){0, 0, 0};
	angle = 10.0f;
	orientation = get_orientation_by_type(mlx->hit_object);
	if (!orientation)
		return ;
	if (key == XK_Down)
		angle = -10.0f;
	angle *= M_PIf / 180.f;
	if (mlx->axis == XK_x)
		rotated = v_rotate(*orientation, (t_vector){1, 0, 0}, angle);
	else if (mlx->axis == XK_y)
		rotated = v_rotate(*orientation, (t_vector){0, 1, 0}, angle);
	else if (mlx->axis == XK_z)
		rotated = v_rotate(*orientation, (t_vector){0, 0, 1}, angle);
	*orientation = v_normalize(rotated);
	mlx->need_render = true;
}
