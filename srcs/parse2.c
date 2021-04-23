/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:12:35 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 17:32:14 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	loop_first_parse(int *g, int *i, t_game *game)
{
	while (*g > 0 && *i)
	{	
		*g = get_next_line(game->fd, &game->str);
		if (*g < 0)
			break ;
		if (!*game->str || check_emtpy_line(game->str))
		{
			free(game->str);
			game->str = 0;
		}
		else
		{
			*i = first_parse(game->str, game);
			if (!*i)
			{	
				check_mapline(game->str, game, *g);
				alloc_map_line(game, game->str);
			}
			free(game->str);
			game->str = 0;
		}
	}
}

int	check_emtpy_line(char *str)
{
	ft_isspace_parse(&str);
	if (*str)
		return (0);
	return (1);
}
