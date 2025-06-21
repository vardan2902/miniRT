/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:29:07 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/21 19:40:19 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	put_pixel(t_mlx_img *img, int x, int y, int color)
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

int	clean_renderer(t_basis *basis, t_ray *ray)
{
	if (basis)
		free(basis);
	free_ray(ray);
	return (0);
}

void	trace_loop(t_mlx *mlx, t_basis *basis, t_viewport *vp, t_ray *ray)
{
	int			y;
	int			x;
	float		sy;
	float		sx;
	t_vector	dir;

	y = -1;
	while (++y < HEIGHT)
	{
		sy = 1.0f - 2.0f * ((y + 0.5f) / (float)HEIGHT);
		x = -1;
		while (++x < WIDTH)
		{
			sx = 2.0f * ((x + 0.5f) / (float)WIDTH) - 1.0f;
			dir = v_add(v_add(
						v_scalar_product(basis->right, sx * (vp->width / 2.0f)),
						v_scalar_product(basis->up, sy * (vp->height / 2.0f))),
					basis->forward);
			assign_vector(v_normalize(dir), ray->orientation);
			put_pixel(mlx->img, x, y, rgb_to_hex(trace_ray(ray, mlx->scene)));
		}
	}
}

int	renderer(void *param)
{
	t_mlx		*mlx;
	t_basis		*basis;
	t_viewport	vp;
	t_ray		*ray;

	mlx = (t_mlx *)param;
	if (!mlx->need_render)
		return (0);
	basis = get_camera_basis(mlx->scene->camera);
	if (!basis)
		return (0);
	vp = compute_viewport_size(mlx->scene->camera->fov);
	ray = (t_ray *)malloc(sizeof (t_ray));
	if (!ray)
		return (clean_renderer(basis, NULL));
	ray->position = mlx->scene->camera->position;
	ray->orientation = (t_vector *)malloc(sizeof (t_vector));
	trace_loop(mlx, basis, &vp, ray);
	clean_renderer(basis, ray);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->img, 0, 0);
	mlx->need_render = false;
	return (0);
}
