/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:06:23 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 19:55:41 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	cleanup_camera(t_camera *camera)
{
	if (!camera)
		return ;
	free(camera->position);
	free(camera->orientation);
	free(camera);
}

void	cleanup_ambient(t_ambient *ambient)
{
	if (!ambient)
		return ;
	free(ambient->rgb);
	free(ambient);
}
