/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:16:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/21 14:43:13 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

int		renderer(void *param);
int		handle_close(void *param);
int		handle_keypress(int key, void *param);
int		handle_mouse_press(int button, int x, int y, void *param);
void	change_camera_orient(char axis, t_mlx *mlx, float angle);

#endif
