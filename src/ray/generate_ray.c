/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:01:55 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/16 16:19:11 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_basis	get_camera_basis(t_vector *forward)
{
	t_vector	world_up;
	t_basis		basis;

	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	if (fabs(v_dot_product(forward, &world_up)) > 0.999f)
		world_up = (t_vector){0, 0, 1};
	basis.forward = v_normalize(forward);
	basis.right = v_normalize(v_cross_product(&world_up, basis.forward));
	basis.up = v_normalize(v_cross_product(basis.forward, basis.right));
	return (basis);
}

static t_viewport	compute_viewport_size(float fov, int width, int height)
{
	float		aspect_ratio;
	t_viewport	vp;

	aspect_ratio = (float)width / (float)height;
	vp.width = 2.0 * tan(fov * 0.5 * M_PI / 180.0);
	vp.height = vp.width / aspect_ratio;
	return (vp);
}

static t_ndc	get_pixel_ndc(int x, int y, int width, int height)
{
	t_ndc	pixel;

	pixel.u = ((x + 0.5f) / (float)width) * 2.0f - 1.0f;
	pixel.v = 1.0f - ((y + 0.5f) / (float)height) * 2.0f;
	return (pixel);
}

t_ray	generate_ray(t_camera *camera, int x, int y)
{
	t_basis		basis;
	t_viewport	vp;
	t_ndc		pixel;
	t_vector	*dir;
	t_ray		ray;

	basis = get_camera_basis(camera->orientation);
	vp = compute_viewport_size(camera->fov, WIDTH, HEIGHT);
	pixel = get_pixel_ndc(x, y, WIDTH, HEIGHT);
	dir = v_add(
			v_add(
				v_scalar_product(basis.right, pixel.u * vp.width * 0.5f),
				v_scalar_product(basis.up, pixel.v * vp.height * 0.5f)
				),
			basis.forward
			);
	dir = v_normalize(dir);
	ray.position = camera->position;
	ray.orientation = dir;
	return (ray);
}
