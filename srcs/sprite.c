/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:03:07 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 18:59:32 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	sort_dist(t_game *game)
{	
	t_sort	sort;
	int		y;

	sort.check = 0;
	sort.i = -1;
	sort.sprites = game->info.spritesdist;
	while (++sort.i < game->count_sprites - 1)
	{	
		y = -1;
		while (++y < game->count_sprites - sort.i - 1)
		{
			if (sort.sprites[y] < sort.sprites[y + 1])
			{
				sort.tmp = sort.sprites[y];
				sort.sprites[y] = sort.sprites[y + 1];
				sort.sprites[y + 1] = sort.tmp;
				sort.tmp2 = game->sprites[y];
				game->sprites[y] = game->sprites[y + 1];
				game->sprites[y + 1] = sort.tmp2;
				sort.check = 1;
			}
		}
		if (!sort.check)
			break ;
	}
}

void	calc_sprite(t_game *game, t_scast *scast, int *i)
{
	scast->sx = game->sprites[*i].x - game->info.px;
	scast->sy = game->sprites[*i].y - game->info.py;
	scast->invdet = 1.0 / (game->info.plane_x
			* game->info.dy - game->info.dx * game->info.plane_y);
	scast->transx = scast->invdet
		* (game->info.dy * scast->sx - game->info.dx * scast->sy);
	scast->transy = scast->invdet
		* (-game->info.plane_y * scast->sx + game->info.plane_x * scast->sy);
	scast->sscreenx = (int)((game->w / 2)
			* (1 + scast->transx / scast->transy));
	scast->sheight = abs((int)(game->h / scast->transy));
	scast->starty = -scast->sheight / 2 + game->h / 2;
	if (scast->starty < 0)
		scast->starty = 0;
	scast->endy = scast->sheight / 2 + game->h / 2;
	if (scast->endy >= game->h)
		scast->endy = game->h - 1;
	scast->swidth = abs((int)(game->h / (scast->transy)));
	scast->startx = -scast->swidth / 2 + scast->sscreenx;
	if (scast->startx < 0)
		scast->startx = 0;
	scast->endx = scast->swidth / 2 + scast->sscreenx;
	if (scast->endx >= game->w)
		scast->endx = game->w - 1;
}

void	sprite_loop(t_game *game, t_scast *scast)
{
	int	y;

	while (scast->startx < scast->endx)
	{
		scast->texx = (int)(256 * (scast->startx - (-scast->swidth / 2
						+ scast->sscreenx)) * scast->img.w
				/ scast->swidth) / 256;
		if (scast->transy > 0 && scast->startx > 0
			&& scast->transy < game->info.zbuf[scast->startx])
		{	
			y = scast->starty;
			while (y < scast->endy)
			{
				scast->d = y * 256 - game->h * 128 + scast->sheight * 128;
				scast->texy = ((scast->d * scast->img.h)
						/ scast->sheight) / 256;
				scast->color = *((scast->img.addr)
						+ scast->img.w * scast->texy + scast->texx);
				if (scast->color)
					my_mlx_pixel_put(game, scast->startx, y, scast->color);
				y++;
			}
		}
		scast->startx++;
	}
}

void	sprite(t_game *game)
{	
	int		i;
	t_scast	scast;

	i = -1;
	scast.img = game->info.textures[4];
	while (++i < game->count_sprites)
	{
		game->info.spritesdist[i] = ((game->info.px - game->sprites[i].x)
				* (game->info.px - game->sprites[i].x)
				+ (game->info.py - game->sprites[i].y)
				* (game->info.py - game->sprites[i].y));
	}
	sort_dist(game);
	i = -1;
	while (++i < game->count_sprites)
	{
		calc_sprite(game, &scast, &i);
		sprite_loop(game, &scast);
	}
}
