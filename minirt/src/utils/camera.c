/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:35:24 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 18:04:48 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	get_cam_right(t_mlx *mlx)
{
	t_vector	forward;
	t_vector	right;
	t_vector	right_cross;

	forward = v_normalize(*mlx->scene->camera->orientation);
	right_cross = v_cross_product(forward, mlx->scene->camera->up);
	right = v_normalize(right_cross);
	return (right);
}

t_vector	get_cam_up(t_mlx *mlx, t_vector right)
{
	t_vector	forward;
	t_vector	up;
	t_vector	up_cross;

	forward = v_normalize(*mlx->scene->camera->orientation);
	up_cross = v_cross_product(right, forward);
	up = v_normalize(up_cross);
	return (up);
}
