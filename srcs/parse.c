/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:11:51 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 22:03:44 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	parsing(char *file, t_game *game)
{
	int		i;
	int		g;

	game->info.mlx = mlx_init();
	if (!game->info.mlx)
		display_error("mlx cannot init", game);
	game->colors[0] = -1;
	game->colors[1] = -1;
	game->fd = open(file, O_RDONLY);
	if (game->fd < 0)
		display_error(strerror(errno), game);
	i = 1;
	g = 1;
	loop_first_parse(&g, &i, game);
	if (g < 0 || i)
		close_fd_and_err("Cannot parse *.cub or missing informations", game);
	verify_params(game);
	parsing_map(game);
}

int	resolution_parse(char *str, t_game *game)
{
	size_t	w;
	size_t	h;
	int		a;
	int		b;

	w = 0;
	h = 0;
	if (game->h || game->w)
		return (close_fd_and_err("Resolution twice", game));
	str++;
	double_atoi(&str, &w, &h);
	if (!w || !h)
		return (close_fd_and_err("Wrong resolution", game));
	mlx_get_screen_size(game->info.mlx, &a, &b);
	if (w > (size_t)a || h > (size_t)b)
	{
		w = a;
		h = b;
	}
	game->h = h;
	game->w = w;
	return (1);
}

int	check_two_letters(char **str)
{	
	int	i;

	i = -2;
	if (!ft_strncmp(*str, "NO", 2))
		i = 0;
	else if (!ft_strncmp(*str, "SO", 2))
		i = 1;
	else if (!ft_strncmp(*str, "WE", 2))
		i = 2;
	else if (!ft_strncmp(*str, "EA", 2))
		i = 3;
	else if (!ft_strncmp(*str, "S", 1))
		i = 4;
	if (i >= 0)
	{
		if (i == 4)
			(*str)++;
		else
			(*str) += 2;
		if (!ft_isspace(**str))
			return (-1);
	}
	return (i);
}

int	textures(char *str, t_game *game, int i)
{
	int		y;
	int		x;
	char	**textures_path;

	textures_path = game->textures_path;
	if (i < 0)
		return (close_fd_and_err("Bad texture's parse", game));
	if (textures_path[i])
		return (close_fd_and_err("Path texture twice", game));
	ft_isspace_parse(&str);
	if (!*str)
		return (0);
	y = 0;
	while (str[y])
		y++;
	textures_path[i] = malloc(sizeof(char) * y + 1);
	if (!textures_path[i])
		return (close_fd_and_err(strerror(errno), game));
	x = -1;
	while (++x < y)
		textures_path[i][x] = str[x];
	textures_path[i][x] = 0;
	return (1);
}
