/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:23:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/13 19:46:44 by ysaroyan         ###   ########.fr       */
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
