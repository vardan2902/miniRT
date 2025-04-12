/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:23:57 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 20:31:15 by ysaroyan         ###   ########.fr       */
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

void	free_and_log(void *obj, char *msg, char *token,
		char **instruction)
{
	log_error(msg, token);
	free(obj);
	free_splitted(instruction);
}

void	free_and_perror(void *obj, char *msg, char **instruction)
{
	perror(msg);
	free(obj);
	free_splitted(instruction);
}
