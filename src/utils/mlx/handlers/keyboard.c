/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:55:22 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 17:56:37 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	handle_keypress(int key, void *param)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (key == XK_Escape)
		handle_close(param);
	handle_camera_rotate(key, mlx);
	handle_light_translation(key, mlx);
	handle_transform_actions(key, mlx);
	return (0);
}
