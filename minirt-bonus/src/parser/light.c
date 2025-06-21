/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:41:01 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/21 21:05:21 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	*build_light(char **line)
{
	t_light	*light;

	light = NULL;
	if (!check_arg_count(line[3])
		|| !create_object((void **)&light, sizeof (t_light))
		|| !set_position(line[0], &light->position)
		|| !set_ratio(line[1], &light->brightness)
		|| !set_rgb(line[2], &light->rgb))
	{
		if (light)
			cleanup_light(light);
		return (NULL);
	}
	return (light);
}
