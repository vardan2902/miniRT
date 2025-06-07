/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:23:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 15:00:47 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_splitted(char **splitted)
{
	int	i;

	if (!splitted)
		return ;
	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
}

void	free_ray(t_ray *ray)
{
	free(ray->orientation);
	free(ray);
}
