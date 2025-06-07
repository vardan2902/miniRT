/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:07:35 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 17:11:49 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_basis	get_world_basis(void)
{
	t_basis	basis;

	basis.forward.x = 0;
	basis.forward.y = 0;
	basis.forward.z = 1;
	basis.right.x = 1;
	basis.right.y = 0;
	basis.right.z = 0;
	basis.up.x = 0;
	basis.up.y = 1;
	basis.up.z = 0;
	return (basis);
}

void	init_scene(t_scene *scene, t_mlx *mlx)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->lights = NULL;
	scene->object_list = NULL;
	scene->mlx = mlx;
	scene->world_basis = get_world_basis();
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
