/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:34:04 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/07 18:58:48 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	int	fd;
	t_mlx	*mlx;

	fd = validate_args(argc, argv);
	(void)fd;
	mlx = init_mlx();
	free(mlx);
	return (0);
}
