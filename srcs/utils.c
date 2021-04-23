/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:09:07 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 18:41:01 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 1;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	ptr = (malloc(sizeof(void) * (size * count)));
	if (!ptr)
		return (0);
	i = 0;
	while (i < (size * count))
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	size;

	size = ft_strlen(s);
	new = ft_calloc(sizeof(char) * (size + 1), 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, size);
	return (new);
}

int	bmp(t_img img, t_game *game)
{
	int	i;
	int	h;
	int	w;

	h = game->h;
	w = game->w;
	game->fd = open("save.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (game->fd < 0)
		return (display_error(strerror(errno), game));
	if (write(game->fd, "BM", 2) < 0)
		return (close_fd_and_err(strerror(errno), game));
	if (write(game->fd, (int []){54 + (w * h) * 4,
			0x00, 0x36, 0x28, w, h, 0x200001, 0, 0, 0x002e23,
			0x002e23, 0, 0}, 52) < 0)
		return (close_fd_and_err(strerror(errno), game));
	i = h - 1;
	while (i >= 0)
	{
		if (write(game->fd, img.addr + i * game->w, game->w * 4) < 0)
			return (close_fd_and_err(strerror(errno), game));
		i--;
	}
	close(game->fd);
	return (quit(game));
}

void	new_image(t_game *game, t_img *img)
{
	img->img = mlx_new_image(game->info.mlx, game->w, game->h);
	if (!img->img)
		display_error("Cannot create image", game);
	img->addr = (int *)mlx_get_data_addr(img->img, &(img->bpp),
			&(img->line), &(img->endian));
}
