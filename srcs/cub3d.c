/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:54:52 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 21:47:30 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	quit(t_game *game)
{
	free(game->info.spritesdist);
	free(game->info.zbuf);
	free(game->sprites);
	free(game->str);
	clean_textures(game);
	if (game->map)
		free_map(game->map, game->rows);
	if (game->info.img.img)
		mlx_destroy_image(game->info.mlx, game->info.img.img);
	if (game->info.win)
		mlx_destroy_window(game->info.mlx, game->info.win);
	if (game->info.mlx)
	{
		mlx_destroy_display(game->info.mlx);
		free(game->info.mlx);
	}
	exit(0);
	return (0);
}

void	calc(t_game *game)
{
	int		x;
	t_cast	ray;
	t_info	*info;

	info = &game->info;
	x = -1;
	while (++x < game->w)
	{	
		ft_bzero(&ray, sizeof(ray));
		ray.cameraX = 2 * x / (double)game->w - 1;
		ray.rx = info->dx + info->plane_x * ray.cameraX;
		ray.ry = info->dy + info->plane_y * ray.cameraX;
		ray.deltaX = fabs(1 / ray.rx);
		ray.deltaY = fabs(1 / ray.ry);
		ray.mapX = (int)info->px;
		ray.mapY = (int)info->py;
		calc_step_side(info, &ray);
		dda(game, &ray);
		dda2(game, &ray);
		choose_good_texture(game, &ray);
		draw_text(game, &ray, x);
		vertical_stripe(game, x, 0, ray.drawStart - 1);
		vertical_stripe(game, x, ray.drawEnd + 1, game->h - 1);
		info->zbuf[x] = ray.perpwall;
	}
}

int	main_loop(t_game *game)
{
	t_info	info;

	info = game->info;
	calc(game);
	sprite(game);
	if (!info.toogle_minimap)
		minimap(game);
	mlx_do_sync(info.mlx);
	if (game->bmp)
		return (bmp(game->info.img, game));
	mlx_put_image_to_window(info.mlx, info.win, info.img.img, 0, 0);
	movement(game);
	return (0);
}

int	init(t_game *game)
{
	init_sprites(game);
	init_game(game);
	init_textures(game);
	game->info.zbuf = malloc(sizeof(double) * game->w);
	if (!game->info.zbuf)
		return (display_error(strerror(errno), game));
	game->info.spritesdist = malloc(sizeof(double) * game->count_sprites);
	if (!game->info.spritesdist)
		return (display_error(strerror(errno), game));
	new_image(game, &game->info.img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	check_arg(argc, argv, &game);
	parsing(argv[1], &game);
	init(&game);
	if (game.bmp)
		return (main_loop(&game));
	if ((game.rows * 6 >= game.h || game.maxline * 6 >= game.w))
	{
		game.minimap = 1;
		game.info.toogle_minimap = 1;
	}
	game.info.win = mlx_new_window(game.info.mlx, game.w, game.h, "cub3D");
	mlx_loop_hook(game.info.mlx, &main_loop, &game);
	mlx_hook(game.info.win, 2, (1L << 0), &key_press, &game);
	mlx_hook(game.info.win, 3, (1L << 1), &key_release, &game);
	mlx_hook(game.info.win, 33, (1L << 17), quit, &game);
	mlx_loop(game.info.mlx);
	return (0);
}
