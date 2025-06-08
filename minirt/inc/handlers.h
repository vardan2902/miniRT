/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:16:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/08 17:24:49 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include <structs.h>

int		renderer(void *param);
int		handle_close(void *param);
int		handle_keypress(int key, void *param);
int		handle_mouse_press(int button, int x, int y, void *param);
int		handle_mouse_release(int button, int x, int y, void *param);
int		handle_mouse_move(int x, int y, void *param);
void	change_light_pos(t_vector *change_vec, t_mlx *mlx);
void	change_camera_orient(char axis, t_mlx *mlx, float angle);

#endif
