/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:34:04 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/07 20:38:44 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	int		fd;
	t_mlx	mlx;

	fd = validate_args(argc, argv);
	close(fd);
	init_mlx(&mlx);
	register_hooks(&mlx);
	return (0);
}
