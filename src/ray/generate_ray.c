/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:01:55 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/24 19:09:15 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_basis	*get_camera_basis(t_vector *forward)
{
	t_vector	world_up;
	t_basis		*basis;
	t_vector	*temp;

	if (!forward)
		return (NULL);
	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	basis = (t_basis *)malloc(sizeof (t_basis));
	if (!basis)
		return (NULL);
	if (fabs(v_dot_product(forward, &world_up)) > 0.999f)
		world_up = (t_vector){0, 0, 1};
	basis->forward = v_normalize(forward);
	temp = v_cross_product(&world_up, basis->forward);
	basis->right = v_normalize(temp);
	free(temp);
	temp = v_cross_product(basis->forward, basis->right);
	basis->up = v_normalize(temp);
	free(temp);
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

t_vector	*get_ray_orientation(t_basis *basis, t_ndc pixel, t_viewport vp)
{
	t_vector	*orient;
	t_vector	*w;
	t_vector	*h;
	t_vector	*total;
	t_vector	*orient_normal;

	w = v_scalar_product(basis->right, pixel.u * vp.width * 0.5f);
	h = v_scalar_product(basis->up, pixel.v * vp.height * 0.5f);
	total = v_add(w,h);
	orient = v_add(total, basis->forward);
	orient_normal = v_normalize(orient);
	free(w);
	free(h);
	free(total);
	free(orient);
	return (orient_normal);
}

t_ray	*generate_ray(t_camera *camera, int x, int y)
{
	t_basis		*basis;
	t_viewport	vp;
	t_ndc		pixel;
	t_ray		*ray;

	ray = (t_ray *)malloc(sizeof (t_ray));
	if (!ray)
		return (NULL);
	basis = get_camera_basis(camera->orientation);
	vp = compute_viewport_size(camera->fov, WIDTH, HEIGHT);
	pixel = get_pixel_ndc(x, y, WIDTH, HEIGHT);
	ray->orientation = get_ray_orientation(basis, pixel, vp);
	free(basis->forward);
	free(basis->up);
	free(basis->right);
	free(basis);
	ray->position = (t_vector *)malloc(sizeof (t_vector));
	if (!ray->position)
	{
		free(ray->orientation);
		free(ray);
		return (NULL);
	}
	ray->position->x = camera->position->x;
	ray->position->y = camera->position->y;
	ray->position->z = camera->position->z;
	return (ray);
}
