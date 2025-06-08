/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:40:05 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/08 17:27:11 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTIONS_H
# define INTERACTIONS_H

# include <stdbool.h>
# include <structs.h>

void	resize_object(t_mlx *mlx, bool is_plus);
void	rotate_object(t_mlx *mlx, float dx, float dy);
void	translate_object(t_mlx *mlx, float dx, float dy);

#endif
