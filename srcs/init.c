/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:14:52 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 18:56:01 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_suffix(char *input, t_game *game)
{
	int	len;

	len = ft_strlen(input);
	if (len > 4)
	{
		if (!ft_strncmp(".cub", &input[len - 4], 4))
			return (1);
	}
	return (display_error("Bad map format: *.cub", game));
}

int	check_arg(int ac, char **av, t_game *game)
{
	if (ac > 3 || ac < 2)
		return (display_error("Wrong number of arguments", game));
	check_suffix(av[1], game);
	if (ac == 3)
	{
		if (ft_strncmp(av[2], "--save", ft_strlen(av[2])))
			return (display_error("Bad second argument must be: --save", game));
		game->bmp = 1;
	}
	return (0);
}

void	init_sprites(t_game *game)
{
	int	i;
	int	y;
	int	x;

	if (game->count_sprites)
	{
		game->sprites = malloc(sizeof(t_sprite) * game->count_sprites);
		if (!game->sprites)
			display_error(strerror(errno), game);
	}
	i = 0;
	x = 0;
	while (++i < game->rows - 1)
	{	
		y = -1;
		while (game->map[i][++y])
		{
			if (game->map[i][y] == '2')
			{
				game->sprites[x].x = i + 0.5;
				game->sprites[x].y = y + 0.5;
				x++;
			}
		}
	}
}

void	init_game(t_game *game)
{
	game->info.px = game->player_row + 0.51;
	game->info.py = game->player_column + 0.51;
	game->info.move = 0.1;
	game->info.rot = 0.05;
	if (game->player == 'N')
	{
		game->info.dx = -1;
		game->info.plane_y = 0.66;
	}
	else if (game->player == 'S')
	{
		game->info.dx = 1;
		game->info.plane_y = -0.66;
	}
	else if (game->player == 'O')
	{
		game->info.dy = 1;
		game->info.plane_x = 0.66;
	}
	else if (game->player == 'O')
	{
		game->info.dy = 1;
		game->info.plane_x = 0.66;
	}
}

int	init_textures(t_game *game)
{
	t_img	img;
	int		i;

	i = -1;
	while (++i < 5)
	{	
		img.img = mlx_xpm_file_to_image(game->info.mlx,
				game->textures_path[i], &img.w, &img.h);
		if (!img.img)
			return (display_error("Cannot load texture", game));
		img.addr = (int *)mlx_get_data_addr(img.img,
				 &img.bpp, &img.line, &img.endian);
		game->info.textures[i] = img;
	}
	return (1);
}
