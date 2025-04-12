/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:33:03 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:29:03 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	set_vector(char **instuction, t_vector *vector)
{
	return (!(!to_float(instuction[0], &vector->x)
			|| !to_float(instuction[1], &vector->y)
			|| !to_float(instuction[2], &vector->z)));
}

void	assign_rgb(char **instuction, t_rgb *rgb)
{
	rgb->r = ft_atoi(instuction[0]);
	rgb->g = ft_atoi(instuction[1]);
	rgb->b = ft_atoi(instuction[2]);
}

bool	create_object(void **obj, size_t size)
{
	*obj = malloc(size);
	if (!obj)
		perror(ERR_MALLOC);
	return (!!*obj);
}

static bool	set_ratio(char *str, double *ratio, void *ptr)
{
	if (!is_in_limit(str, RATIO_MIN, RATIO_MAX)
		|| !to_float(str, ratio))
	{
		free_and_log(ptr, ERR_INVALID_TOKEN, str, NULL);
		return (false);
	}
	return (true);
}

static bool	set_position(char *str, t_vector *pos, void *ptr)
{
	char	**position;

	position = ft_split(str, ',');
	if (!position)
	{
		free_and_perror(ptr, ERR_MALLOC, NULL);
		return (false);
	}
	if (!is_instruction_in_range(position, -DBL_MAX, DBL_MAX, 3)
		|| !set_vector(position, pos))
	{
		free_and_log(ptr, ERR_INVALID_TOKEN, str, position);
		return (false);
	}
	free_splitted(position);
	return (true);
}

static bool	set_orientation(char *str, t_vector *orient, void *ptr)
{
	char	**orientation;

	orientation = ft_split(str, ',');
	if (!orientation)
	{
		free_and_perror(ptr, ERR_MALLOC, NULL);
		return (false);
	}
	if (!is_instruction_in_range(orientation, ORIENT_MIN, ORIENT_MAX, 3)
		|| !set_vector(orientation, orient))
	{
		free_and_log(ptr, ERR_INVALID_TOKEN, str, NULL);
		free_splitted(orientation);
		return (false);
	}
	free_splitted(orientation);
	return (true);
}

static bool	check_rgb(char **rgb, char *str, void *ptr)
{
	if (!rgb)
	{
		free_and_perror(ptr, ERR_MALLOC, NULL);
		return (false);
	}
	if (!is_instruction_in_range(rgb, RGB_MIN, RGB_MAX, 3))
	{
		free_and_log(ptr, ERR_INVALID_TOKEN, str, rgb);
		return (false);
	}
	return (true);
}

static bool	set_rgb(char *str, t_rgb *color, void *ptr)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!check_rgb(rgb, str, ptr))
		return (false);
	assign_rgb(rgb, color);
	free_splitted(rgb);
	return (true);
}

static bool	check_arg_count(char *str)
{
	if (!str)
		return (true);
	log_error(ERR_INVALID_TOKEN, str);
	return (false);
}

static void	*build_ambient(char **line)
{
	t_ambient	*ambient;

	if (!check_arg_count(line[2])
		|| !create_object((void **)&ambient, sizeof (t_ambient))
		|| !set_ratio(line[0], &ambient->lighting, ambient)
		|| !set_rgb(line[1], &ambient->rgb, ambient))
		return (NULL);
	return (ambient);
}

static void	*build_camera(char **line)
{
	t_camera	*camera;

	if (!check_arg_count(line[3])
		|| !create_object((void **)&camera, sizeof (t_camera))
		|| !set_position(line[0], &camera->position, camera)
		|| !set_orientation(line[1], &camera->orientation, camera))
		return (NULL);
	if (!is_in_limit(line[2], DEG_MIN, DEG_MAX)
		|| !to_float(line[2], &camera->fov))
	{
		free_and_log(camera, ERR_INVALID_TOKEN, line[2], NULL);
		return (NULL);
	}
	return (camera);
}

static void	*build_light(char **line)
{
	t_light	*light;
	char	**rgb;

	if (!check_arg_count(line[3])
		|| !create_object((void **)&light, sizeof (t_light))
		|| !set_position(line[0], &light->position, light)
		|| !set_ratio(line[1], &light->brightness, light))
		return (NULL);
	rgb = ft_split(line[2], ',');
	if (!check_rgb(rgb, line[2], light))
	{
		free_splitted(rgb);
		return (NULL);
	}
	free_splitted(rgb);
	return (light);
}

static void	*build_sphere(char **line)
{
	t_sphere	*sphere;

	if (!check_arg_count(line[3])
		|| !create_object((void **)&sphere, sizeof (t_sphere))
		|| !set_position(line[0], &sphere->position, sphere))
		return (NULL);
	if (!is_in_limit(line[1], -DBL_MAX, DBL_MAX)
		|| !to_float(line[1], &sphere->diameter))
	{
		free_and_log(sphere, ERR_INVALID_TOKEN, line[1], NULL);
		return (NULL);
	}
	if (!set_rgb(line[2], &sphere->rgb, sphere))
		return (NULL);
	return (sphere);
}

static void	*build_plane(char **line)
{
	t_plane	*plane;

	if (!check_arg_count(line[3])
		|| !create_object((void **)&plane, sizeof (t_plane))
		|| !set_position(line[0], &plane->position, plane)
		|| !set_orientation(line[1], &plane->orientation, plane)
		|| !set_rgb(line[2], &plane->rgb, plane))
		return (NULL);
	return (plane);
}

static void	*build_cylinder(char **line)
{
	t_cylinder	*cylinder;

	if (!check_arg_count(line[5])
		|| !create_object((void **)&cylinder, sizeof (t_cylinder))
		|| !set_position(line[0], &cylinder->position, cylinder)
		|| !set_orientation(line[1], &cylinder->orientation, cylinder))
		return (NULL);
	if (!is_in_limit(line[2], -DBL_MAX, DBL_MAX)
		|| !to_float(line[2], &cylinder->diameter))
	{
		free_and_log(cylinder, ERR_INVALID_TOKEN, line[2], NULL);
		return (NULL);
	}
	if (!is_in_limit(line[3], -DBL_MAX, DBL_MAX)
		|| !to_float(line[3], &cylinder->height))
	{
		free_and_log(cylinder, ERR_INVALID_TOKEN, line[3], NULL);
		return (NULL);
	}
	if (!set_rgb(line[4], &cylinder->rgb, cylinder))
		return (NULL);
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

bool	parse_object(void **obj, char **line, char *id, void *(build)(char **))
{
	if (*obj)
	{
		log_error(ERR_ID_DUP, id);
		return (false);
	}
	*obj = build(line);
	return (!!*obj);
}

bool	parse_line(t_scene *scene, char *id, char **line)
{
	if (!ft_strcmp(id, AMBIENT))
		return (parse_object((void **)&scene->ambient, line, id,
				build_ambient));
	if (!ft_strcmp(id, CAMERA))
		return (parse_object((void **)&scene->camera, line, id, build_camera));
	if (!ft_strcmp(id, LIGHT))
		return (parse_object((void **)&scene->light, line, id, build_light));
	if (!ft_strcmp(id, SPHERE))
		return (assign_object_list(&scene->sphere_list, line,
				build_sphere));
	if (!ft_strcmp(id, CYLINDER))
		return (assign_object_list(&scene->cylinder_list, line,
				build_cylinder));
	if (!ft_strcmp(id, PLANE))
		return (assign_object_list(&scene->plane_list, line,
				build_plane));
	return (false);
}
