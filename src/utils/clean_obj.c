/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:06:23 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/13 18:06:44 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	cleanup_camera(t_camera *camera)
{
	if (camera)
	{
		free(camera->position);
		free(camera->orientation);
		free(camera);
	}
}

void	cleanup_ambient(t_ambient *ambient)
{
	if (ambient)
	{
		free(ambient->rgb);
		free(ambient);
	}
}

void	cleanup_light(t_light *light)
{
	if (light)
	{
		free(light->position);
		free(light);
	}
}
