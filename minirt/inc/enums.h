/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:48:01 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/21 17:39:50 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum e_object_types
{
	E_AMBIENT,
	E_CAMERA,
	E_LIGHT,
	E_SPHERE,
	E_CYLINDER,
	E_PLANE,
};

enum e_mouse_keys
{
	LEFT_CLICK = Button1,
	RIGHT_CLICK = Button3,
	SCROLL_UP = Button4,
	SCROLL_DOWN = Button5,
};

#endif
