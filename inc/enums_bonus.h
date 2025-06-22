/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:23:18 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 19:06:55 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_BONUS_H
# define ENUMS_BONUS_H

# include <X11/X.h>

enum e_object_types
{
	E_SPHERE,
	E_CYLINDER,
	E_PLANE,
	E_CONE
};

enum e_mouse_keys
{
	LEFT_CLICK = Button1,
	RIGHT_CLICK = Button3,
	SCROLL_UP = Button4,
	SCROLL_DOWN = Button5,
};

#endif
