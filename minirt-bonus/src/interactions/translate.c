/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:27:43 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/21 14:49:13 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_object(t_mlx *mlx, int key)
{
	t_vector	*position;
	float		dir;
	float		speed;

	dir = 2.0f;
	if (key == XK_Down)
		dir = -2.0f;
	position = get_position_by_type(mlx->hit_object);
	if (!position)
		return ;
	speed = v_length(v_sub(*position, *mlx->scene->camera->position)) * 0.01f;
	if (mlx->axis == XK_x)
		position->x += dir * speed;
	else if (mlx->axis == XK_y)
		position->y += dir * speed;
	else if (mlx->axis == XK_z)
		position->z += dir * speed;
	mlx->need_render = true;
}
