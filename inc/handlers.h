/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:16:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/26 16:45:04 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

int		renderer(void *param);
int		handle_close(void *param);
int		handle_keypress(int key, void *param);
int		handle_mouse_press(int button, int x, int y, void *param);
int		handle_mouse_release(int button, int x, int y, void *param);
int		handle_mouse_move(int x, int y, void *param);
void	change_light_pos(t_vector *change_vec, t_mlx *mlx);
void	change_camera_orient(t_vector *change_vec, t_mlx *mlx, float scale);

#endif
