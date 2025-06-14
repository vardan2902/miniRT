/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:34:04 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/14 19:31:31 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	int		fd;
	t_mlx	mlx;
	t_scene	scene;

	fd = validate_args(argc, argv);
	mlx.ptr = mlx_init();
	if (!mlx.ptr)
		throw_error("mlx_init failed");
	init_scene(&scene, &mlx);
	parse_scene(&scene, fd);
	close(fd);
	mlx.scene = &scene;
	init_mlx(&mlx);
	register_hooks(&mlx);
	return (0);
}
