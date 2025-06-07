/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:47:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 17:24:29 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

bool	check_rgb(char **rgb, char *str)
{
	if (!rgb)
	{
		perror(ERR_MALLOC);
		return (false);
	}
	if (!is_instruction_in_range(rgb, RGB_MIN, RGB_MAX, 3))
	{
		log_error(ERR_INVALID_TOKEN, str);
		free(rgb);
		return (false);
	}
	return (true);
}

bool	check_arg_count(char *str)
{
	if (!str)
		return (true);
	log_error(ERR_INVALID_TOKEN, str);
	return (false);
}

bool	assign_object_list(t_scene *scene, enum e_object_types type, char **line,
	void *(build)(t_mlx *, char **))
{
	t_list		*new;
	t_object	*object;
	void		*new_obj;

	new_obj = build(scene->mlx, line);
	if (!create_object((void **)&object, sizeof (t_object)))
		return (false);
	if (!new_obj)
	{
		free(object);
		return (false);
	}
	object->object = new_obj;
	object->type = type;
	object->checkerboard = false;
	new = ft_lstnew(object);
	if (!new)
		return (false);
	ft_lstadd_back(&scene->object_list, new);
	return (true);
}
