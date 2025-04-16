/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:42:33 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/14 19:24:26 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include <minirt.h>

bool	intersect(t_object *object, t_ray ray, t_hit *hit);
bool	intersect_sphere(t_ray ray, t_object *sphere, t_hit *hit);
bool	intersect_plane(t_ray ray, t_object *object, t_hit *hit);

#endif
