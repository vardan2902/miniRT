/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:34:04 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/11 20:43:24 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	init_scene(t_scene *scene)
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
	if (!scene)
		return ;
	free(scene->camera);
	free(scene->ambient);
	free(scene->light);
	ft_lstclear(&scene->sphere_list, free);
	ft_lstclear(&scene->plane_list, free);
	ft_lstclear(&scene->cylinder_list, free);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_mlx	mlx;
	char	*line;
	char	**splitted;
	char	*error_msg;
	t_scene	scene;

	fd = validate_args(argc, argv);
	line = get_next_line(fd);
	init_scene(&scene);
	while (line)
	{
		if (is_line_empty(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		splitted = ft_split_charset(line, " \t\v\r\f\n");
		if (!splitted)
		{
			cleanup_scene(&scene);
			break ;
		}
		if (!is_identifier(splitted[0]))
		{
			free_splitted(splitted);
			error_msg = ft_strjoin("miniRT: wrong identifier", splitted[0]);
			log_error(error_msg);
			break ;
		}
		if (!parse_line(&scene, splitted[0], splitted + 1))
		{
			free_splitted(splitted);
			break ;
		}
		free_splitted(splitted);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
	{
		while (line)
		{
			free(line);
			line = get_next_line(fd);
		}
		exit(EXIT_FAILURE);
	}
	if (!scene.camera)
	{
		free(scene.ambient);
		free(scene.light);
		ft_lstclear(&scene.sphere_list, free);
		ft_lstclear(&scene.plane_list, free);
		ft_lstclear(&scene.cylinder_list, free);
		throw_error("miniRT: mandatory property camera is not provided");
	}
	else if (!scene.ambient && !scene.light)
	{
		free(scene.camera);
		ft_lstclear(&scene.sphere_list, free);
		ft_lstclear(&scene.plane_list, free);
		ft_lstclear(&scene.cylinder_list, free);
		throw_error("miniRT: mandatory property camera is not provided");
	}
	close(fd);
	print_scene(&scene);
	(void)mlx;
	init_mlx(&mlx);
	register_hooks(&mlx);
	cleanup_scene(&scene);

	return (0);
}
