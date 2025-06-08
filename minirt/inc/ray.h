/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:38:30 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/08 17:28:01 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <structs.h>

t_rgb	trace_ray(t_ray *ray, t_scene *scene);
void	generate_ray(t_ray *ray, t_ndc pixel, t_basis *basis, t_viewport vp);

#endif
