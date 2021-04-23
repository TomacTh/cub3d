/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:08:04 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 18:41:34 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_map(char **map, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
		free(map[i]);
	free(map);
	map = 0;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (*(unsigned char *)s1 == *(unsigned char *)s2
		&& *(unsigned char *)s1 && *(unsigned char *)s2 && --n)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	vertical_stripe(t_game *game, int x, int y1, int y2)
{	
	int	color;

	if (!y1)
		color = game->colors[1];
	else
		color = game->colors[0];
	while (y1 <= y2)
	{	
		my_mlx_pixel_put(game, x, y1, color);
		y1++;
	}
}

int	display_error(char *str, t_game *game)
{
	printf("Error\n%s\n", str);
	return (quit(game));
}

int	close_fd_and_err(char *str, t_game *game)
{
	if (game->fd >= 0)
		close(game->fd);
	return (display_error(str, game));
}
