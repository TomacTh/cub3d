/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:38:11 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 17:54:52 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	rgb(char **str, size_t *el, int i)
{
	ft_isspace_parse(str);
	if (!(**str >= '0' && **str <= '9'))
		return (0);
	while (**str >= '0' && **str <= '9')
	{
		*el = *el * 10 + (**str - '0');
		(*str)++;
	}
	ft_isspace_parse(str);
	if (*el > 255)
		return (0);
	if (i)
	{
		if (**str != ',')
			return (0);
		(*str)++;
	}
	else
	{
		if (**str)
			return (0);
	}
	return (1);
}

int	parse_color(char *str, int *color, t_game *game)
{	
	size_t	r;
	size_t	g;
	size_t	b;

	r = 0;
	g = 0;
	b = 0;
	if (*color >= 0)
		return (close_fd_and_err("Color given twice", game));
	str++;
	if (!rgb(&str, &r, 1))
		return (close_fd_and_err("Bad color must be: R, G, B", game));
	if (!rgb(&str, &g, 1))
		return (close_fd_and_err("Bad color must be: R, G, B", game));
	if (!rgb(&str, &b, 0))
		return (close_fd_and_err("Bad color must be: R, G, B", game));
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

int	verify_params(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (!game->textures_path[i])
			return (close_fd_and_err("Missing a texture", game));
	}
	if (game->colors[0] == -1 || game->colors[1] == -1 )
		return (close_fd_and_err("Missing while floor or ceil color", game));
	if (!game->w || !game->h)
		return (close_fd_and_err("Resolution error", game));
	return (0);
}

int	first_parse(char *str, t_game *game)
{
	int		i;

	i = check_two_letters(&str);
	if (i > -2)
		return (textures(str, game, i));
	else if (*str == 'C' && ft_isspace(*(str + 1)))
		return (parse_color(str, &game->colors[1], game));
	else if (*str == 'F' && ft_isspace(*(str + 1)))
		return (parse_color(str, &game->colors[0], game));
	else if (*str == 'R' && ft_isspace(*(str + 1)))
		return (resolution_parse(str, game));
	ft_isspace_parse(&str);
	if (*str != '1')
		return (close_fd_and_err("Missing or incorrect map", game));
	return (0);
}
