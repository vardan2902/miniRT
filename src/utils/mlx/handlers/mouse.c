/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:54:47 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 20:24:42 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	handle_scroll(int button, int x, int y, t_mlx *mlx)
{
	if (button == SCROLL_UP)
	{
		if (!pick_object_at(x, y, mlx->scene, &mlx->hit_object)
			|| mlx->hit_object->type == E_PLANE)
			return (0);
		resize_object(mlx, true);
		mlx->need_render = true;
	}
	else if (button == SCROLL_DOWN)
	{
		if (!pick_object_at(x, y, mlx->scene, &mlx->hit_object)
			|| mlx->hit_object->type == E_PLANE)
			return (0);
		resize_object(mlx, false);
		mlx->need_render = true;
	}
	return (1);
}

int	handle_mouse_press(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		handle_scroll(button, x, y, mlx);
	if (button == LEFT_CLICK)
	{
		pick_object_at(x, y, mlx->scene, &mlx->hit_object);
		mlx->need_render = true;
	}
	return (0);
}
