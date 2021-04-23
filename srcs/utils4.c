/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:41:54 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 18:26:54 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	ft_isspace_parse(char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
}

int	alloc_map_line(t_game *game, char *str)
{
	game->rows++;
	if (game->rows > 1)
		realloc_map(game);
	else
	{
		game->map = malloc(sizeof(char *) * game->rows);
		if (!game->map)
			return (close_fd_and_err(strerror(errno), game));
	}
	game->map[game->rows - 1] = ft_strdup(str);
	if (!game->map[game->rows - 1])
		return (close_fd_and_err(strerror(errno), game));
	return (0);
}

int	key_press(int key, t_game *game)
{	
	t_move	*movement;

	movement = &game->info.movement;
	if (key == FORWARD_W_Z)
		movement->forward = 1;
	if (key == BACK_S_S)
		movement->back = 1;
	if (key == RIGHT_D_D)
		movement->right = 1;
	if (key == LEFT_A_Q)
		movement->left = 1;
	if (key == ROTATE_RIGHT)
		movement->rotright = 1;
	if (key == ROTATE_LEFT)
		movement->rotleft = 1;
	if (key == MINIMAP && game->minimap == 0)
	{
		if (game->info.toogle_minimap == 0)
			game->info.toogle_minimap = 1;
		else if (game->info.toogle_minimap)
			game->info.toogle_minimap = 0;
	}
	else if (key == ESCAPE)
		return (quit(game));
	return (0);
}
