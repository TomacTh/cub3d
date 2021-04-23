/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:44:07 by tcharvet          #+#    #+#             */
/*   Updated: 2021/04/22 22:19:04 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	front_back(t_game *game, t_move *movement, t_info *info)
{
	if (movement->forward)
	{
		if (game->map[(int)(info->px + info->dx * (info->move * 2))]
		[(int)(info->py)] == '0' && game->map[(int)(info->px)]
		[(int)(info->py + info->dy * (info->move * 2))] == '0')
		{
			info->px += info->dx * info->move;
			info->py += info->dy * info->move;
		}
	}
	if (movement->back)
	{
		if (game->map[(int)(info->px - info->dx * info->move * 2)]
		[(int)(info->py)] == '0' && game->map[(int)(info->px)]
		[(int)(info->py - info->dy * info->move * 2)] == '0')
		{
			info->px -= info->dx * info->move;
			info->py -= info->dy * info->move;
		}	
	}
}

void	right_left(t_game *game, t_move *movement, t_info *info)
{
	if (movement->right)
	{	
		if (game->map[(int)(info->px + info->dy * info->move * 2)]
		[(int)(info->py)] == '0' && game->map[(int)(info->px)]
		[(int)(info->py - info->dx * info->move * 2)] == '0')
		{
			info->px += info->dy * info->move;
			info->py -= info->dx * info->move;
		}
	}
	if (movement->left)
	{
		if (game->map[(int)(info->px - info->dy * info->move * 2)]
		[(int)(info->py)] == '0' && game->map[(int)(info->px)]
		[(int)(info->py + info->dx * info->move * 2)] == '0')
		{
			info->px -= info->dy * info->move;
			info->py += info->dx * info->move;
		}
	}
}

void	rotation(t_move *movement, t_info *info)
{
	if (movement->rotright)
	{
		movement->tdx = info->dx;
		movement->tplane_x = info->plane_x;
		info->dx = info->dx * cos(-info->rot) - info->dy * sin(-info->rot);
		info->dy = movement->tdx * sin(-info->rot) + info->dy * cos(-info->rot);
		movement->tplane_x = info->plane_x;
		info->plane_x = info->plane_x * cos(-info->rot)
			- info->plane_y * sin(-info->rot);
		info->plane_y = movement->tplane_x * sin(-info->rot)
			+ info->plane_y * cos(-info->rot);
	}
	if (movement->rotleft)
	{
		movement->tdx = info->dx;
		info->dx = info->dx * cos(info->rot) - info->dy * sin(info->rot);
		info->dy = movement->tdx * sin(info->rot) + info->dy * cos(info->rot);
		movement->tplane_x = info->plane_x;
		info->plane_x = info->plane_x
			* cos(info->rot) - info->plane_y * sin(info->rot);
		info->plane_y = movement->tplane_x * sin(info->rot)
			+ info->plane_y * cos(info->rot);
	}
}

void	movement(t_game *game)
{
	t_move	*movement;
	t_info	*info;

	info = &game->info;
	movement = &info->movement;
	front_back(game, movement, info);
	right_left(game, movement, info);
	rotation(movement, info);
}

int	key_release(int key, t_game *game)
{
	if (key == FORWARD_W_Z || key == BACK_S_S
		|| key == BACK_S_S || key == RIGHT_D_D || key == LEFT_A_Q
		|| key == ROTATE_LEFT || key == ROTATE_RIGHT)
	{
		ft_bzero(&game->info.movement, sizeof(t_move));
	}
	return (0);
}
