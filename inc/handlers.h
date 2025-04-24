/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:16:59 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/21 19:41:07 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

int	renderer(void *param);
int	handle_close(void *param);
int	handle_keypress(int key, void *param);
int	handle_mouse_press(int button, int x, int y, void *param);
int	handle_mouse_release(int button, int x, int y, void *param);
int	handle_mouse_move(int x, int y, void *param);

#endif
