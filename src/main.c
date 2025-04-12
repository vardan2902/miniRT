/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:34:04 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/04/12 18:52:16 by ysaroyan         ###   ########.fr       */
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
	print_scene(&scene);
	init_mlx(&mlx);
	register_hooks(&mlx);
	cleanup_scene(&scene);
	return (0);
}
