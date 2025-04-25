/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:29:07 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/25 16:58:54 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*data;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	data = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)data = color;
}

unsigned int	rgb_to_hex(t_rgb color)
{
	unsigned int	hex;

	hex = 0x00 << 24;
	hex |= (color.r << 16);
	hex |= (color.g << 8);
	hex |= (color.b);
	return (hex);
}

int	renderer(void *param)
{
	t_mlx	*mlx;
	t_ray	*ray;
	t_rgb	color;
	int		y;
	int		x;

	mlx = (t_mlx *)param;
	if (!mlx->need_render)
		return (0);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(mlx->scene->camera, x, y);
			if (!ray)
			{
				mlx->need_render = false;
				return (0);
			}
			color = trace_ray(ray, mlx->scene);
			free(ray->position);
			free(ray->orientation);
			free(ray);
			put_pixel(mlx->img, x, y, rgb_to_hex(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
	mlx->need_render = false;
	return (0);
}
