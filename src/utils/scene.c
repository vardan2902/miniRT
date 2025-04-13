/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:07:35 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/13 18:07:57 by ysaroyan         ###   ########.fr       */
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
	cleanup_camera(scene->camera);
	scene->camera = NULL;
	cleanup_ambient(scene->ambient);
	scene->ambient = NULL;
	cleanup_light(scene->light);
	scene->light = NULL;
	ft_lstclear(&scene->sphere_list, del_sphere);
	scene->sphere_list = NULL;
	ft_lstclear(&scene->plane_list, del_plane);
	scene->plane_list = NULL;
	ft_lstclear(&scene->cylinder_list, del_cylinder);
	scene->cylinder_list = NULL;
}
