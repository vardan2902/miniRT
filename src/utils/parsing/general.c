/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_anun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:47:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:48:27 by ysaroyan         ###   ########.fr       */
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

bool	check_rgb(char **rgb, char *str, void *ptr)
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

bool	check_arg_count(char *str)
{
	if (!str)
		return (true);
	log_error(ERR_INVALID_TOKEN, str);
	return (false);
}

bool	assign_object_list(t_list **list, char **line,
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
