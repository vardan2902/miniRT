/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:51:22 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 17:53:22 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	change_light_pos(t_vector *change_vec, t_mlx *mlx)
{
	t_vector	light_pos;

	light_pos = v_add(*mlx->scene->light->position, *change_vec);
	*mlx->scene->light->position = light_pos;
	mlx->need_render = true;
}

void	handle_light_translation(int key, t_mlx *mlx)
{
	if (key == XK_l)
		change_light_pos(&(t_vector){6.0f, 0, 0}, mlx);
	else if (key == XK_j)
		change_light_pos(&(t_vector){-6.0f, 0, 0}, mlx);
	else if (key == XK_i)
		change_light_pos(&(t_vector){0, 6.0f, 0}, mlx);
	else if (key == XK_k)
		change_light_pos(&(t_vector){0, -6.0f, 0}, mlx);
	else if (key == XK_o)
		change_light_pos(&(t_vector){0, 0, 6.0f}, mlx);
	else if (key == XK_u)
		change_light_pos(&(t_vector){0, 0, -6.0f}, mlx);
}
