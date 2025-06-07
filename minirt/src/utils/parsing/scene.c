/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:51:42 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/07 17:34:39 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	check_mandatory_props(t_scene *scene)
{
	if (scene->camera && scene->ambient && scene->light)
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

static void	cleanup_line(char *line, t_scene *scene)
{
	if (!line)
		return ;
	get_next_line(-1);
	cleanup_scene(scene);
	exit(EXIT_FAILURE);
}

static bool	process_line(t_scene *scene, char *line)
{
	char	**splitted;

	splitted = ft_split_charset(line, " \t\v\r\f\n");
	if (!splitted)
		return (false);
	if (!is_identifier(splitted[0]))
	{
		log_error(ERR_WRONG_ID, splitted[0]);
		free_splitted(splitted);
		return (false);
	}
	if (!parse_line(scene, splitted[0], splitted + 1))
	{
		free_splitted(splitted);
		return (false);
	}
	free_splitted(splitted);
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

void	parse_scene(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_line_empty(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!process_line(scene, line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	cleanup_line(line, scene);
	check_mandatory_props(scene);
}
