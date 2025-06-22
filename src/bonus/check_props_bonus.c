/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_props_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:12:02 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 18:13:15 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	check_mandatory_props(t_scene *scene)
{
	if (scene->camera && scene->ambient && scene->lights)
		return ;
	if (!scene->camera)
		log_error(ERR_MANDATORY_C, NULL);
	else if (!scene->ambient)
		log_error(ERR_MANDATORY_A, NULL);
	else
		log_error(ERR_MANDATORY_L, NULL);
	cleanup_scene(scene);
	exit(EXIT_FAILURE);
}
