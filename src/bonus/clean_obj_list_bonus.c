/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_obj_list_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:07:28 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 18:22:20 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	del_sphere(void	*content)
{
	t_sphere	*sp;

	sp = (t_sphere *)content;
	free(sp->position);
	free(sp->rgb);
	free(sp->bumpmap);
	free(sp);
}

void	del_plane(void	*content)
{
	t_plane	*p;

	p = (t_plane *)content;
	free(p->position);
	free(p->orientation);
	free(p->rgb);
	free(p->bumpmap);
	free(p);
}

void	del_cylinder(void	*content)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)content;
	free(cy->position);
	free(cy->orientation);
	free(cy->rgb);
	free(cy->bumpmap);
	free(cy);
}

void	del_cone(void	*content)
{
	t_cone	*co;

	co = (t_cone *)content;
	free(co->position);
	free(co->orientation);
	free(co->rgb);
	free(co->bumpmap);
	free(co);
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
	if (object->type == E_CONE)
		del_cone(object->object);
	free(object);
}
