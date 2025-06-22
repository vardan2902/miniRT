/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:07:30 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 18:07:51 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	assign_object_list(t_list **list, enum e_object_types type, char **line,
	void *(build)(char **))
{
	t_list		*new;
	t_object	*object;
	void		*new_obj;

	new_obj = build(line);
	if (!create_object((void **)&object, sizeof (t_object)))
		return (false);
	if (!new_obj)
	{
		free(object);
		return (false);
	}
	object->object = new_obj;
	object->type = type;
	new = ft_lstnew(object);
	if (!new)
		return (false);
	ft_lstadd_back(list, new);
	return (true);
}
