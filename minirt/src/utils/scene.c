/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:07:35 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 20:36:22 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	init_scene(t_scene *scene, t_mlx *mlx)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->object_list = NULL;
	scene->mlx = mlx;
}

void	cleanup_scene(t_scene *scene)
{
	cleanup_camera(scene->camera);
	scene->camera = NULL;
	cleanup_ambient(scene->ambient);
	scene->ambient = NULL;
	cleanup_light(scene->light);
	scene->light = NULL;
	ft_lstclear(&scene->object_list, del_object);
	scene->object_list = NULL;
}
