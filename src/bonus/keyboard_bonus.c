/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:55:49 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 17:55:58 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	handle_checkerboard(t_mlx *mlx)
{
	t_list		*obj;
	t_object	*object;

	obj = mlx->scene->object_list;
	while (obj)
	{
		object = (t_object *)obj->content;
		object->checkerboard = !object->checkerboard;
		obj = obj->next;
	}
	mlx->need_render = true;
}

int	handle_keypress(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == XK_Escape)
		handle_close(param);
	if (key == XK_1)
		handle_checkerboard(mlx);
	handle_camera_rotate(key, mlx);
	handle_transform_actions(key, mlx);
	return (0);
}
