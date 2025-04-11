/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:23:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/09 18:33:02 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minirt.h>

void	free_splitted(char **splitted)
{
	int	i;

	i = -1;
	if (!splitted)
		return ;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
}
