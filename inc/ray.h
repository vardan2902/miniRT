/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:38:30 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/16 14:36:08 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <structs.h>

t_rgb	trace_ray(t_ray ray, t_scene *scene);
t_ray	generate_ray(t_camera *camera, int x, int y);

#endif
