/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:34:04 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/06/22 16:34:58 by vapetros         ###   ########.fr       */
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
		throw_error(ERR_MLX_INIT);
	init_scene(&scene, &mlx);
	parse_scene(mlx.ptr, &scene, fd);
	close(fd);
	mlx.scene = &scene;
	init_mlx(&mlx);
	register_hooks(&mlx);
	return (0);
}
