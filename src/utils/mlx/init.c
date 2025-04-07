/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:59:05 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/07 17:05:28 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	register_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, KeyPress, KeyPressMask, handle_keypress, mlx);
	mlx_hook(mlx->win, DestroyNotify, NoEventMask, handle_close, mlx);
	mlx_loop(mlx->ptr);
}

t_mlx	*init_mlx()
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof (t_mlx));
	if (!mlx)
		throw_error("Error\n");
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		throw_error("Error\n");
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, TITLE);
	if (!mlx->win)
		throw_error("Error\n");
	register_hooks(mlx);
	return (mlx);
}
