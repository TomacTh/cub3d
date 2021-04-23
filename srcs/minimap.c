/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:26:03 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 17:26:12 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	minimap_lines(t_game *game, int x, int y, int color)
{	
	int	i;
	int	l;

	if (x)
		x *= 6;
	if (y)
		y *= 6;
	i = -1;
	l = 6;
	while (l--)
		my_mlx_pixel_put(game, x + l, y + 5, 0x0);
	while (++i < 5)
	{	
		l = 0;
		while (l < 5)
		{	
			my_mlx_pixel_put(game, x + l, y + i, color);
			l++;
		}
		my_mlx_pixel_put(game, x + 5, y + i, 0x0);
	}
}

void	minimap_color(char c, int *color)
{
	if (c == '1')
		*color = 0x565554e;
	else if (c == '2')
		*color = 0xffd000;
	else if (c == '0')
		*color = 0xe1e0d9;
	else
		*color = 0;
}

void	minimap(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = -1;
	while (++y < (int)game->rows)
	{
		x = -1;
		while (game->map[y][++x])
		{	
			if ((int)game->info.px == y && (int)game->info.py == x)
				color = 0xF94525;
			else
				minimap_color(game->map[y][x], &color);
			if (color)
				minimap_lines(game, x, y, color);
		}
	}
}
