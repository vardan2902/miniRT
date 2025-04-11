/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:33:03 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/11 20:02:39 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	*build_ambient(char **line)
{
	t_ambient	*ambient;
	char		**rgb;
	char		*error_msg;

	if (line[2])
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		return (NULL);
	}
	ambient = (t_ambient *)malloc(sizeof (t_ambient));
	if (!ambient)
	{
		perror("Error\nminiRT: malloc");
		return (NULL);
	}
	if (!is_in_limit(line[0], RATIO_MIN, RATIO_MAX)
		|| !set_float(line[0], &ambient->lighting))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[0]);
		log_error(error_msg);
		free(error_msg);
		free(ambient);
		return (NULL);
	}
	rgb = ft_split(line[1], ',');
	if (!rgb)
	{
		perror("Error\nminiRT: malloc");
		free(ambient);
		return (NULL);
	}
	if (!is_instruction_in_range(rgb, RGB_MIN, RGB_MAX, 3))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[1]);
		log_error(error_msg);
		free(error_msg);
		free(ambient);
		free_splitted(rgb);
		return (NULL);
	}
	ambient->rgb.r = ft_atoi(rgb[0]);
	ambient->rgb.g = ft_atoi(rgb[1]);
	ambient->rgb.b = ft_atoi(rgb[2]);
	free_splitted(rgb);
	return (ambient);
}

static void	*build_camera(char **line)
{
	t_camera	*camera;
	char		**position;
	char		**orientation;
	char		*error_msg;

	if (line[3])
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		return (NULL);
	}
	camera = (t_camera *)malloc(sizeof (t_camera));
	if (!camera)
	{
		perror("Error\nminiRT: malloc");
		return (NULL);
	}
	position = ft_split(line[0], ',');
	if (!position)
	{
		perror("Error\nminiRT: malloc");
		free(camera);
		return (NULL);
	}
	if (!is_instruction_in_range(position, -DBL_MAX, DBL_MAX, 3)
		|| !set_float(position[0], &camera->position.x)
		|| !set_float(position[1], &camera->position.y)
		|| !set_float(position[2], &camera->position.z))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[0]);
		log_error(error_msg);
		free(error_msg);
		free(camera);
		free_splitted(position);
		return (NULL);
	}
	orientation = ft_split(line[1], ',');
	if (!orientation)
	{
		perror("Error\nminiRT: malloc");
		free(camera);
		free_splitted(position);
		return (NULL);
	}
	if (!is_instruction_in_range(orientation, ORIENTATION_MIN,
			ORIENTATION_MAX, 3)
		|| !set_float(orientation[0], &camera->orientation.x)
		|| !set_float(orientation[1], &camera->orientation.y)
		|| !set_float(orientation[2], &camera->orientation.z))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[1]);
		log_error(error_msg);
		free(error_msg);
		free(camera);
		free_splitted(position);
		free_splitted(orientation);
		return (NULL);
	}
	if (!is_in_limit(line[2], DEG_MIN, DEG_MAX)
		|| !set_float(line[2], &camera->fov))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		free(camera);
		free_splitted(position);
		free_splitted(orientation);
		return (NULL);
	}
	free_splitted(position);
	free_splitted(orientation);
	return (camera);
}

static void	*build_light(char **line)
{
	t_light	*light;
	char	**position;
	char	*error_msg;

	if (line[3])
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		return (NULL);
	}
	light = (t_light *)malloc(sizeof (t_light));
	if (!light)
	{
		perror("Error\nminiRT: malloc");
		return (NULL);
	}
	position = ft_split(line[0], ',');
	if (!position)
	{
		perror("Error\nminiRT: malloc");
		free(light);
		return (NULL);
	}
	if (!is_instruction_in_range(position, -DBL_MAX, DBL_MAX, 3)
		|| !set_float(position[0], &light->position.x)
		|| !set_float(position[1], &light->position.y)
		|| !set_float(position[2], &light->position.z))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[0]);
		log_error(error_msg);
		free(error_msg);
		free(light);
		free_splitted(position);
		return (NULL);
	}
	if (!is_in_limit(line[1], RATIO_MIN, RATIO_MAX)
		|| !set_float(line[1], &light->brightness))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[1]);
		log_error(error_msg);
		free(error_msg);
		free(light);
		free_splitted(position);
		return (NULL);
	}
	free_splitted(position);
	return (light);
}

static void	*build_sphere(char **line)
{
	t_sphere	*sphere;
	char		**position;
	char		**rgb;
	char		*error_msg;

	if (line[3])
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		return (NULL);
	}
	sphere = (t_sphere *)malloc(sizeof (t_sphere));
	if (!sphere)
	{
		perror("Error\nminiRT: malloc");
		return (NULL);
	}
	if (!is_in_limit(line[1], -DBL_MAX, DBL_MAX)
		|| !set_float(line[1], &sphere->diameter))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[1]);
		log_error(error_msg);
		free(error_msg);
		free(sphere);
		return (NULL);
	}
	position = ft_split(line[0], ',');
	if (!position)
	{
		perror("Error\nminiRT: malloc");
		free(sphere);
		return (NULL);
	}
	if (!is_instruction_in_range(position, -DBL_MAX, DBL_MAX, 3)
		|| !set_float(position[0], &sphere->position.x)
		|| !set_float(position[1], &sphere->position.y)
		|| !set_float(position[2], &sphere->position.z))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[0]);
		log_error(error_msg);
		free(error_msg);
		free(sphere);
		free_splitted(position);
		return (NULL);
	}
	rgb = ft_split(line[2], ',');
	if (!rgb)
	{
		perror("Error\nminiRT: malloc");
		free(sphere);
		free_splitted(position);
		return (NULL);
	}
	if (!is_instruction_in_range(rgb, RGB_MIN, RGB_MAX, 3))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		free(sphere);
		free_splitted(position);
		free_splitted(rgb);
		return (NULL);
	}
	sphere->rgb.r = ft_atoi(rgb[0]);
	sphere->rgb.g = ft_atoi(rgb[1]);
	sphere->rgb.b = ft_atoi(rgb[2]);
	free_splitted(position);
	free_splitted(rgb);
	return (sphere);
}

static void	*build_plane(char **line)
{
	t_plane	*plane;
	char	**position;
	char	**orientation;
	char	**rgb;
	char	*error_msg;

	if (line[3])
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		return (NULL);
	}
	plane = (t_plane *)malloc(sizeof (t_plane));
	if (!plane)
	{
		perror("Error\nminiRT: malloc");
		return (NULL);
	}
	position = ft_split(line[0], ',');
	if (!position)
	{
		perror("Error\nminiRT: malloc");
		free(plane);
		return (NULL);
	}
	if (!is_instruction_in_range(position, -DBL_MAX, DBL_MAX, 3)
		|| !set_float(position[0], &plane->position.x)
		|| !set_float(position[1], &plane->position.y)
		|| !set_float(position[2], &plane->position.z))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[0]);
		log_error(error_msg);
		free(error_msg);
		free(plane);
		free_splitted(position);
		return (NULL);
	}
	orientation = ft_split(line[1], ',');
	if (!orientation)
	{
		perror("Error\nminiRT: malloc");
		free(plane);
		free_splitted(position);
		return (NULL);
	}
	if (!is_instruction_in_range(orientation, ORIENTATION_MIN,
			ORIENTATION_MAX, 3)
		|| !set_float(orientation[0], &plane->orientation.x)
		|| !set_float(orientation[1], &plane->orientation.y)
		|| !set_float(orientation[2], &plane->orientation.z))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[1]);
		log_error(error_msg);
		free(error_msg);
		free(plane);
		free_splitted(position);
		free_splitted(orientation);
		return (NULL);
	}
	rgb = ft_split(line[2], ',');
	if (!rgb)
	{
		perror("Error\nminiRT: malloc");
		free(plane);
		free_splitted(position);
		free_splitted(orientation);
		return (NULL);
	}
	if (!is_instruction_in_range(rgb, RGB_MIN, RGB_MAX, 3))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		free(plane);
		free_splitted(position);
		free_splitted(orientation);
		free_splitted(rgb);
		return (NULL);
	}
	plane->rgb.r = ft_atoi(rgb[0]);
	plane->rgb.g = ft_atoi(rgb[1]);
	plane->rgb.b = ft_atoi(rgb[2]);
	free_splitted(rgb);
	free_splitted(position);
	free_splitted(orientation);
	return (plane);
}

static void	*build_cylinder(char **line)
{
	t_cylinder	*cylinder;
	char	**position;
	char	**orientation;
	char	**rgb;
	char	*error_msg;

	if (line[5])
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		return (NULL);
	}
	cylinder = (t_cylinder *)malloc(sizeof (t_cylinder));
	if (!cylinder)
	{
		perror("Error\nminiRT: malloc");
		return (NULL);
	}
	if (!is_in_limit(line[2], -DBL_MAX, DBL_MAX)
		|| !set_float(line[2], &cylinder->diameter))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[2]);
		log_error(error_msg);
		free(error_msg);
		free(cylinder);
		return (NULL);
	}
	if (!is_in_limit(line[3], -DBL_MAX, DBL_MAX)
		|| !set_float(line[3], &cylinder->height))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[3]);
		log_error(error_msg);
		free(error_msg);
		free(cylinder);
		return (NULL);
	}
	position = ft_split(line[0], ',');
	if (!position)
	{
		perror("Error\nminiRT: malloc");
		free(cylinder);
		return (NULL);
	}
	if (!is_instruction_in_range(position, -DBL_MAX, DBL_MAX, 3)
		|| !set_float(position[0], &cylinder->position.x)
		|| !set_float(position[1], &cylinder->position.y)
		|| !set_float(position[2], &cylinder->position.z))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[0]);
		log_error(error_msg);
		free(error_msg);
		free(cylinder);
		free_splitted(position);
		return (NULL);
	}
	orientation = ft_split(line[1], ',');
	if (!orientation)
	{
		perror("Error\nminiRT: malloc");
		free(cylinder);
		free_splitted(position);
		return (NULL);
	}
	if (!is_instruction_in_range(orientation, ORIENTATION_MIN,
			ORIENTATION_MAX, 3)
		|| !set_float(orientation[0], &cylinder->orientation.x)
		|| !set_float(orientation[1], &cylinder->orientation.y)
		|| !set_float(orientation[2], &cylinder->orientation.z))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[1]);
		log_error(error_msg);
		free(error_msg);
		free(cylinder);
		free_splitted(position);
		free_splitted(orientation);
		return (NULL);
	}
	rgb = ft_split(line[4], ',');
	if (!rgb)
	{
		perror("Error\nminiRT: malloc");
		free(cylinder);
		free_splitted(position);
		free_splitted(orientation);
		return (NULL);
	}
	if (!is_instruction_in_range(rgb, RGB_MIN, RGB_MAX, 3))
	{
		error_msg = ft_strjoin("miniRT: Invalid token: ", line[4]);
		log_error(error_msg);
		free(error_msg);
		free(cylinder);
		free_splitted(position);
		free_splitted(orientation);
		free_splitted(rgb);
		return (NULL);
	}
	cylinder->rgb.r = ft_atoi(rgb[0]);
	cylinder->rgb.g = ft_atoi(rgb[1]);
	cylinder->rgb.b = ft_atoi(rgb[2]);
	free_splitted(rgb);
	free_splitted(position);
	free_splitted(orientation);
	return (cylinder);
}

static bool	assign_object_list(t_list **list, char **line,
	void *(build)(char **))
{
	t_list	*new;
	void	*new_obj;

	new_obj = build(line);
	if (!new_obj)
		return (false);
	new = ft_lstnew(new_obj);
	if (!new)
		return (false);
	ft_lstadd_back(list, new);
	return (true);
}

static bool	assign_object(void **scene_obj, char **line,
	void *(build)(char **))
{
	*scene_obj = build(line);
	return (!!*scene_obj);
}

bool	parse_line(t_scene *scene, char *identifier, char **line)
{
	if (!ft_strcmp(identifier, AMBIENT))
		return (assign_object((void **)&scene->ambient, line, build_ambient));
	if (!ft_strcmp(identifier, CAMERA))
		return (assign_object((void **)&scene->camera, line, build_camera));
	if (!ft_strcmp(identifier, LIGHT))
		return (assign_object((void **)&scene->light, line, build_light));
	if (!ft_strcmp(identifier, SPHERE))
		return (assign_object_list(&scene->sphere_list, line,
				build_sphere));
	if (!ft_strcmp(identifier, CYLINDER))
		return (assign_object_list(&scene->cylinder_list, line,
				build_cylinder));
	if (!ft_strcmp(identifier, PLANE))
		return (assign_object_list(&scene->plane_list, line,
				build_plane));
	return (false);
}
