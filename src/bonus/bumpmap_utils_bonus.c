/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:14:09 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 18:21:03 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

float	get_bump_height(t_bumpmap *bumpmap, float u, float v)
{
	int	x;
	int	y;
	int	color;
	int	r;

	if (!bumpmap || !bumpmap->pixels)
		return (0.0f);
	x = (int)(u * bumpmap->width) % bumpmap->width;
	y = (int)(v * bumpmap->height) % bumpmap->height;
	color = bumpmap->pixels[y * bumpmap->width + x];
	r = (color >> 16) & 0xFF;
	return (r / 255.0f);
}

t_rgb	get_color_from_bumpmap(t_bumpmap *bumpmap, float u, float v)
{
	t_rgb	color;
	int		pixel;
	int		x;
	int		y;

	x = (int)(u * bumpmap->width) % bumpmap->width;
	y = (int)(v * bumpmap->height) % bumpmap->height;
	if (x < 0)
		x += bumpmap->width;
	if (y < 0)
		y += bumpmap->height;
	pixel = bumpmap->pixels[y * bumpmap->width + x];
	color.r = (pixel >> 16) & 0xFF;
	color.g = (pixel >> 8) & 0xFF;
	color.b = (pixel) & 0xFF;
	return (color);
}

void	get_bumped(t_map_props *props)
{
	props->bumped = (t_vector){
		props->sampled.x * props->tangent.x + props->sampled.y
		* props->bitangent.x + props->sampled.z * props->n.x,
		props->sampled.x * props->tangent.y + props->sampled.y
		* props->bitangent.y + props->sampled.z * props->n.y,
		props->sampled.x * props->tangent.z + props->sampled.y
		* props->bitangent.z + props->sampled.z * props->n.z
	};
}

void	get_sampled(t_map_props *props)
{
	props->sampled = (t_vector){
		(props->color.r / 255.0f) * 2.0f - 1.0f,
		(props->color.g / 255.0f) * 2.0f - 1.0f,
		(props->color.b / 255.0f) * 2.0f - 1.0f};
}
