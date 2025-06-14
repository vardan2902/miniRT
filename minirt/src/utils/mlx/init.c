/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:59:05 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 19:32:54 by vapetros         ###   ########.fr       */
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

static t_basis	get_world_basis(void)
{
	t_basis	basis;

	basis.forward.x = 0;
	basis.forward.y = 0;
	basis.forward.z = 1;
	basis.right.x = 1;
	basis.right.y = 0;
	basis.right.z = 0;
	basis.up.x = 0;
	basis.up.y = 1;
	basis.up.z = 0;
	return (basis);
}

void	init_mlx(t_mlx *mlx)
{
	t_mlx_img	*img;

	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, TITLE);
	if (!mlx->win)
		throw_error("mlx_new_window failed");
	img = (t_mlx_img *)malloc(sizeof (t_mlx_img));
	if (!img)
		perror(ERR_MALLOC);
	img->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!img->img)
		throw_error("image creation failed");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	mlx->img = img;
	mlx->scene->world_basis = get_world_basis();
	mlx->need_render = true;
}
