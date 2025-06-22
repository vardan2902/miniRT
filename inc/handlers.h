/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:16:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 17:57:33 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include <minirt.h>

int		renderer(void *param);
int		handle_close(void *param);
void	handle_camera_rotate(int key, t_mlx *mlx);
void	handle_transform_actions(int key, t_mlx *mlx);
int		handle_keypress(int key, void *param);
int		handle_mouse_press(int button, int x, int y, void *param);
void	change_camera_orient(char axis, t_mlx *mlx, float angle);

#endif
