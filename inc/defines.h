/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:49:14 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:33:47 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIDTH 800
# define HEIGHT 600
# define TITLE "miniRT"

# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define CYLINDER "cy"
# define PLANE "pl"

# define RATIO_MIN 0.0
# define RATIO_MAX 1.0
# define ORIENT_MIN -1.0
# define ORIENT_MAX 1.0
# define RGB_MIN 0.0
# define RGB_MAX 255.0
# define DEG_MIN 0.0
# define DEG_MAX 180.0

# define ERR_INVALID_TOKEN "miniRT: Invalid token: "
# define ERR_MALLOC "Error\nminiRT: malloc"
# define ERR_ID_DUP "miniRT: identifier duplication: "
# define ERR_MANDATORY_C "miniRT: mandatory property `C' not provided"
# define ERR_MANDATORY_AL "miniRT: mandatory property `A' or `L' not provided"
# define ERR_WRONG_ID "miniRT: wrong identifier: "

#endif
