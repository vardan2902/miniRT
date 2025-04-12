/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:41:44 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:42:00 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_sphere(char **line)
{
	t_sphere	*sphere;

	if (!check_arg_count(line[3])
		|| !create_object((void **)&sphere, sizeof (t_sphere))
		|| !set_position(line[0], &sphere->position, sphere))
		return (NULL);
	if (!is_in_limit(line[1], -DBL_MAX, DBL_MAX)
		|| !to_float(line[1], &sphere->diameter))
	{
		free_and_log(sphere, ERR_INVALID_TOKEN, line[1], NULL);
		return (NULL);
	}
	if (!set_rgb(line[2], &sphere->rgb, sphere))
		return (NULL);
	return (sphere);
}
