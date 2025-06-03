/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:41:44 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/13 18:56:06 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_sphere(char **line)
{
	t_sphere	*sphere;

	sphere = NULL;
	if (!check_arg_count(line[3])
		|| !create_object((void **)&sphere, sizeof (t_sphere))
		|| !set_position(line[0], &sphere->position)
		|| !set_prop(line[1], &sphere->diameter)
		|| !set_prop(line[1], &sphere->initial_diameter)
		|| !set_rgb(line[2], &sphere->rgb))
	{
		del_sphere(sphere);
		return (NULL);
	}
	return (sphere);
}
