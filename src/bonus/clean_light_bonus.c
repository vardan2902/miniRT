/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:24:16 by vapetros          #+#    #+#             */
/*   Updated: 2025/06/22 18:25:13 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	cleanup_light(void *content)
{
	t_light	*light;

	light = (t_light *)content;
	if (!light)
		return ;
	free(light->position);
	free(light->rgb);
	free(light);
}
