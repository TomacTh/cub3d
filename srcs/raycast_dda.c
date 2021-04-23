/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:46:02 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 16:47:52 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calc_step_side(t_info *info, t_cast *ry)
{
	if (ry->rx < 0)
	{
		ry->stepX = -1;
		ry->sideX = (info->px - ry->mapX) * ry->deltaX;
	}
	else
	{
		ry->stepX = 1;
		ry->sideX = (ry->mapX + 1.0 - info->px) * ry->deltaX;
	}
	if (ry->ry < 0)
	{
		ry->stepY = -1;
		ry->sideY = (info->py - ry->mapY) * ry->deltaY;
	}
	else
	{
		ry->stepY = 1;
		ry->sideY = (ry->mapY + 1.0 - info->py) * ry->deltaY;
	}
}

void	dda(t_game *game, t_cast *ray)
{
	while (!ray->hit)
	{
		if (ray->sideX < ray->sideY)
		{	
			ray->sideX += ray->deltaX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{	
			ray->sideY += ray->deltaY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->map[ray->mapX][ray->mapY] == '1')
			ray->hit = 1;
	}
}

void	dda2(t_game *game, t_cast *ray)
{	
	if (!ray->side)
	{
		ray->perpwall = (ray->mapX - game->info.px + (1 - ray->stepX) / 2)
			/ ray->rx;
		ray->wallX = game->info.py + ray->perpwall * ray->ry;
	}
	else
	{
		ray->perpwall = (ray->mapY - game->info.py + (1 - ray->stepY) / 2)
			/ ray->ry;
		ray->wallX = game->info.px + ray->perpwall * ray->rx;
	}
	ray->wallX -= floor(ray->wallX);
	ray->lineHeight = (int) game->h / ray->perpwall;
	ray->drawStart = -ray->lineHeight / 2 + game->h / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->drawStart + ray->lineHeight;
	if (ray->drawEnd >= game->h)
		ray->drawEnd = game->h - 1;
	if (ray->drawEnd < 0)
	{
		ray->drawEnd = game->h - 1;
		ray->drawStart = 0;
	}
}

void	choose_good_texture(t_game *game, t_cast *ray)
{
	if (ray->side)
	{
		if (ray->ry > 0)
			ray->i = 3;
		else
			ray->i = 2;
	}
	else
	{
		if (ray->rx > 0)
			ray->i = 1;
		else
			ray->i = 0;
	}
	ray->img = game->info.textures[ray->i];
}

void	draw_text(t_game *game, t_cast *ray, int x)
{
	t_img	img;
	int		y;

	img = ray->img;
	ray->texx = (int)(ray->wallX * (double)img.w);
	if ((!ray->side && ray->rx > 0) || (ray->side && ray->ry < 0))
		ray->texx = img.w - ray->texx - 1;
	ray->step = 1.0 * img.w / ray->lineHeight;
	ray->textpos = (ray->drawStart - game->h
			/ 2 + ray->lineHeight / 2) * ray->step;
	y = ray->drawStart;
	while (y <= ray->drawEnd)
	{
		ray->texy = (int)ray->textpos & (img.h - 1);
		ray->textpos += ray->step;
		ray->color = *((img.addr) + img.w * ray->texy + ray->texx);
		my_mlx_pixel_put(game, x, y, ray->color);
		y++;
	}
}
