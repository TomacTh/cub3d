/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:08:59 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 18:40:31 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	clean_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (game->info.textures[i].img)
			mlx_destroy_image(game->info.mlx, game->info.textures[i].img);
	}
	i = -1;
	while (++i < 5)
		free(game->textures_path[i]);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdst;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (dst != src)
	{
		while (n--)
		{
			*pdst = *psrc;
			++pdst;
			++psrc;
		}
	}
	return (dst);
}

void	double_atoi(char **str, size_t *w, size_t *h)
{
	ft_isspace_parse(str);
	while (**str >= '0' && **str <= '9')
	{
		*w = *w * 10 + (**str - '0');
		(*str)++;
	}
	ft_isspace_parse(str);
	while (**str >= '0' && **str <= '9')
	{
		*h = *h * 10 + (**str - '0');
		(*str)++;
	}
	ft_isspace_parse(str);
	if (**str)
		*w = 0;
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	int		*dst;
	t_img	*data;

	data = &game->info.img;
	dst = data->addr + (y * game->w + x);
	*(unsigned int *)dst = color;
}
