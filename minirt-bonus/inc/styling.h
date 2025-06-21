/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   styling.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:18:01 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 19:18:14 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STYLING_H
# define STYLING_H

# include <minirt.h>

t_vector	get_bumped_orient(t_hit *hit);
t_rgb		get_checker_color(t_vector point, t_object *object);

#endif
