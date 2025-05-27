/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:01:55 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 20:17:41 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_basis	*get_camera_basis(t_vector *forward)
{
	t_vector	world_up;
	t_basis		*basis;

	world_up.x = 0.0f;
	world_up.y = 1.0f;
	world_up.z = 0.0f;
	basis = (t_basis *)malloc(sizeof (t_basis));
	if (!basis)
		return (NULL);
	if (fabs(v_dot_product(world_up, *forward)) > 0.999f)
		world_up = (t_vector){1.0f, 0.0f, 0.0f};
	assign_vector(*forward, &basis->forward);
	assign_vector(v_normalize(v_cross_product(basis->forward, world_up)),
		&basis->right);
	assign_vector(v_normalize(v_cross_product(basis->right, basis->forward)),
		&basis->up);
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

	pixel.u = ((x + 0.5f) / (float)WIDTH) * 2.0f - 1.0f;
	pixel.v = 1.0f - ((y + 0.5f) / (float)HEIGHT) * 2.0f;
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
