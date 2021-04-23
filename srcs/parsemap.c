/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:26:38 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/23 01:02:23 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
		return (1);
	return (0);
}

int	check_mapline(char *str, t_game *game, int g)
{	
	int	i;

	i = 0;
	if (check_emtpy_line(str) && g)
		return (close_fd_and_err("Emtpty line in map", game));
	while (str[i])
	{
		if (!ft_isspace(str[i]) && !(str[i] >= 48
				&& str[i] <= 50) && !is_player(str[i]))
			return (close_fd_and_err("Wrong characters in map", game));
		if (is_player(str[i]) && game->player)
			return (close_fd_and_err("Position player given twice", game));
		if (is_player(str[i]))
		{
			game->player = str[i];
			game->player_row = game->rows;
			game->player_column = i;
			str[i] = '0';
		}
		if (str[i] == '2')
			game->count_sprites++;
		i++;
	}
	return (0);
}

int	verify_close_map(char *str, t_game *game, int row)
{
	size_t	i;
	int		tab;

	tab = 0;
	i = 0;
	while (str[i])
	{	
		if(str[i] == '\t')
			tab += 4;
		if (str[i] == '0' || str[i] == '2')
		{
			if (!row || !i || row == game->rows - 1)
				return (display_error("Map error", game));
			if (!(str[i - 1] >= 48 && str[i - 1] <= 50))
				return (display_error("Map error", game));
			if (!(str[i + 1] >= 48 && str[i + 1] <= 50))
				return (display_error("Map error", game));
			if (!(game->map[row - 1][i + tab] >= 48 && game->map[row - 1][i + tab] <= 50))
				return (display_error("Map error", game));
			if (!(game->map[row + 1][i + tab] >= 48 && game->map[row + 1][i + tab] <= 50))
				return (display_error("Map error", game));
		}
		if (str[i] == '1' && i > (size_t)game->maxline)
			game->maxline = i;
		i++;
	}
	return (0);
}

int	parsing_map(t_game *game)
{
	int	g;

	g = 1;
	while (g > 0)
	{
		g = get_next_line(game->fd, &game->str);
		if (g < 0)
			return (close_fd_and_err("GNL error", game));
		check_mapline(game->str, game, g);
		alloc_map_line(game, game->str);
		free(game->str);
		game->str = 0;
	}
	close(game->fd);
	if (game->rows < 3)
		return (display_error("Wrong map, 3 lines minimum", game));
	if (!game->player)
		return (display_error("No player position", game));
	g = -1;
	while (++g < (int)game->rows)
		verify_close_map(game->map[g], game, g);
	return (0);
}

int	realloc_map(t_game *game)
{
	char	**temp;
	int		i;

	i = -1;
	if (game->rows > 1)
	{
		temp = malloc(sizeof(char *) * game->rows);
		while (++i < game->rows - 1)
		{
			temp[i] = ft_strdup(game->map[i]);
			if (!temp[i])
			{
				free_map(temp, i);
				free_map(game->map, game->rows);
				return (close_fd_and_err(strerror(errno), game));
			}
		}
		free_map(game->map, game->rows - 1);
		game->map = temp;
	}
	return (0);
}
