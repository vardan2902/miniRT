/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:35:47 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 18:35:52 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	init_scene(t_scene *scene, t_mlx *mlx)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->lights = NULL;
	scene->object_list = NULL;
	scene->mlx = mlx;
}

void	cleanup_scene(t_scene *scene)
{
	cleanup_camera(scene->camera);
	scene->camera = NULL;
	cleanup_ambient(scene->ambient);
	scene->ambient = NULL;
	ft_lstclear(&scene->lights, cleanup_light);
	scene->lights = NULL;
	ft_lstclear(&scene->object_list, del_object);
	scene->object_list = NULL;
}
