/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:59:05 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 18:04:04 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	register_hooks(t_mlx *mlx)
{
	mlx->hit_object = NULL;
	mlx->axis = 0;
	mlx->action = 0;
	mlx_hook(mlx->win, KeyPress, KeyPressMask, handle_keypress, mlx);
	mlx_hook(mlx->win, DestroyNotify, NoEventMask, handle_close, mlx);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, handle_mouse_press, mlx);
	mlx_loop_hook(mlx->ptr, renderer, mlx);
	mlx_loop(mlx->ptr);
}

void	init_mlx(t_mlx *mlx)
{
	t_mlx_img	*img;

	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, TITLE);
	if (!mlx->win)
		throw_error(ERR_MLX_WIN);
	img = (t_mlx_img *)malloc(sizeof (t_mlx_img));
	if (!img)
		perror(ERR_MALLOC);
	img->img = (t_img *)mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!img->img)
		throw_error(ERR_MLX_IMG);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	mlx->img = img;
	mlx->need_render = true;
}
