/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:26:56 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/26 20:29:38 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	change_light_pos(t_vector *change_vec, t_mlx *mlx)
{
	t_vector	*light_pos;

	light_pos = v_add(mlx->scene->light->position, change_vec);
	*mlx->scene->light->position = *light_pos;
	mlx->need_render = true;
	free(light_pos);
}

void	change_camera_orient(t_vector *change_vec, t_mlx *mlx, float scale)
{
	t_vector	*cam_orient;

	cam_orient = v_rotate(mlx->scene->camera->orientation, change_vec, scale);
	*mlx->scene->camera->orientation = *v_normalize(cam_orient);
	mlx->need_render = true;
	free(cam_orient);
}
