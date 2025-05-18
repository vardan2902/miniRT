/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:16:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 19:21:42 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

int		renderer(void *param);
int		handle_close(void *param);
int		handle_keypress(int key, void *param);
// int		handle_mouse_press(int button, int x, int y, void *param);
// int		handle_mouse_release(int button, int x, int y, void *param);
// int		handle_mouse_move(int x, int y, void *param);
// void	change_light_pos(t_vector *change_vec, t_mlx *mlx);
// void	change_camera_orient(t_vector change_vec, t_mlx *mlx, float scale);
void	change_camera_orient(char key, t_mlx *mlx, float scale);

#endif
