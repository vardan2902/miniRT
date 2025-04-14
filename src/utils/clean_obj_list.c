/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_obj_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:07:28 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 17:48:56 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	del_sphere(void	*content)
{
	t_sphere	*sp;

	sp = (t_sphere *)content;
	free(sp->position);
	free(sp->rgb);
	free(sp);
}

void	del_plane(void	*content)
{
	t_plane	*p;

	p = (t_plane *)content;
	free(p->position);
	free(p->orientation);
	free(p->rgb);
	free(p);
}

void	del_cylinder(void	*content)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)content;
	free(cy->position);
	free(cy->orientation);
	free(cy->rgb);
	free(cy);
}

void	del_object(void	*content)
{
	t_object	*object;

	object = (t_object *)content;
	if (object->type == E_CYLINDER)
		del_cylinder(object->object);
	if (object->type == E_PLANE)
		del_plane(object->object);
	if (object->type == E_SPHERE)
		del_sphere(object->object);
	free(object);
}
