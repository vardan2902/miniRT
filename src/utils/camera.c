/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:35:24 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/26 19:36:10 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	*get_cam_right(t_mlx *mlx)
{
	t_vector	*forward;
	t_vector	*right;
	t_vector	*right_cross;

	forward = v_normalize(mlx->scene->camera->orientation);
	right_cross = v_cross_product(forward, &(t_vector){0, 1.0f, 0});
	right = v_normalize(right_cross);
	free(forward);
	free(right_cross);
	return (right);
}

t_vector	*get_cam_up(t_mlx *mlx, t_vector *right)
{
	t_vector	*forward;
	t_vector	*up;
	t_vector	*up_cross;

	forward = v_normalize(mlx->scene->camera->orientation);
	up_cross = v_cross_product(right, forward);
	up = v_normalize(up_cross);
	free(forward);
	free(up_cross);
	return (up);
}
