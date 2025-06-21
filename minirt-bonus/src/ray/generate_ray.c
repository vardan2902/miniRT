/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:01:55 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 21:12:16 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_basis	*get_camera_basis(t_camera *camera)
{
	t_basis	*basis;

	basis = malloc(sizeof(t_basis));
	if (!basis)
		return (NULL);
	basis->right = v_normalize(v_cross_product(camera->up,
				*camera->orientation));
	basis->up = v_normalize(v_cross_product(*camera->orientation,
				basis->right));
	basis->forward = *camera->orientation;
	return (basis);
}

t_viewport	compute_viewport_size(float fov)
{
	float		aspect_ratio;
	float		h_fov_rad;
	float		v_fov_rad;
	t_viewport	vp;

	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	h_fov_rad = fov * M_PI / 180.0f;
	v_fov_rad = 2.0f * atanf(tanf(h_fov_rad / 2.0f) / aspect_ratio);
	vp.height = 2.0f * tanf(v_fov_rad / 2.0f);
	vp.width = vp.height * aspect_ratio;
	return (vp);
}

t_ndc	get_pixel_ndc(int x, int y)
{
	t_ndc	pixel;

	pixel.u = 2.0f * ((x + 0.5f) / (float)WIDTH) - 1.0f;
	pixel.v = 1.0f - 2.0f * ((y + 0.5f) / (float)HEIGHT);
	return (pixel);
}

t_vector	get_ray_orientation(t_basis *basis, t_ndc pixel, t_viewport vp)
{
	t_vector	orient;
	t_vector	w;
	t_vector	h;
	t_vector	total;
	t_vector	orient_normal;

	w = v_scalar_product(basis->right, pixel.u * vp.width * 0.5f);
	h = v_scalar_product(basis->up, pixel.v * vp.height * 0.5f);
	total = v_add(w, h);
	orient = v_add(total, basis->forward);
	orient_normal = v_normalize(orient);
	return (orient_normal);
}

void	generate_ray(t_ray *ray, t_ndc pixel, t_basis *basis, t_viewport vp)
{
	ray->orientation = (t_vector *)malloc(sizeof (t_vector));
	if (!ray->orientation)
		return ;
	assign_vector(get_ray_orientation(basis, pixel, vp), ray->orientation);
}
