/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:41:44 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 21:11:56 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_sphere(t_mlx *mlx, char **line)
{
	t_sphere	*sphere;
	bool		has_bumpmap;
	char		*last_str;

	sphere = NULL;
	if (!create_object((void **)&sphere, sizeof (t_sphere)))
		return (NULL);
	sphere->bumpmap = NULL;
	has_bumpmap = false;
	last_str = line[3];
	if (line[3])
	{
		has_bumpmap = true;
		last_str = line[4];
	}
	if (!check_arg_count(last_str)
		|| !set_position(line[0], &sphere->position)
		|| !set_prop(line[1], &sphere->diameter)
		|| !set_prop(line[1], &sphere->initial_diameter)
		|| !set_rgb(line[2], &sphere->rgb)
		|| (has_bumpmap && !set_bumpmap(mlx, line[3], &sphere->bumpmap)))
	{
		return (NULL);
	}
	return (sphere);
}
