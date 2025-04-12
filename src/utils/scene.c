/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:07:35 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 18:55:18 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	init_scene(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->cylinder_list = NULL;
	scene->plane_list = NULL;
	scene->sphere_list = NULL;
}

void	cleanup_scene(t_scene *scene)
{
	free(scene->camera);
	free(scene->ambient);
	free(scene->light);
	ft_lstclear(&scene->sphere_list, free);
	ft_lstclear(&scene->plane_list, free);
	ft_lstclear(&scene->cylinder_list, free);
}
