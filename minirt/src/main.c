/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:34:04 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/05/18 18:43:48 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	int		fd;
	t_mlx	mlx;
	t_scene	scene;

	fd = validate_args(argc, argv);
	init_scene(&scene);
	parse_scene(&scene, fd);
	close(fd);
	mlx.scene = &scene;
	init_mlx(&mlx);
	register_hooks(&mlx);
	return (0);
}
