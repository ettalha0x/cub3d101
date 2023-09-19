/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:40:13 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 00:40:41 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	move_left(t_data *data)
{
	int			target_x;
	int			target_y;
	t_coords	destination;

	destination.x = cos(data->player_ang * (M_PI / 180));
	destination.y = sin(data->player_ang * (M_PI / 180));
	target_x = (int)(data->player->x + (0.22 * destination.y));
	target_y = (int)(data->player->y - (0.22 * destination.x));
	if (data->map[target_y][target_x] != '1'
		&& data->map[target_y][(int)data->player->x] != '1'
		&& data->map[(int)data->player->y][target_x] != '1')
	{
		data->player->x += 0.1 * destination.y;
		data->player->y -= 0.1 * destination.x;
	}
}

static void	move_right(t_data *data)
{
	int			target_x;
	int			target_y;
	t_coords	destination;

	destination.x = cos(data->player_ang * (M_PI / 180));
	destination.y = sin(data->player_ang * (M_PI / 180));
	target_x = (int)(data->player->x - (0.22 * destination.y));
	target_y = (int)(data->player->y + (0.22 * destination.x));
	if (data->map[target_y][target_x] != '1'
		&& data->map[target_y][(int)data->player->x] != '1'
		&& data->map[(int)data->player->y][target_x] != '1')
	{
		data->player->x -= 0.1 * destination.y;
		data->player->y += 0.1 * destination.x;
	}
}

static void	move_down(t_data *data)
{
	int			target_x;
	int			target_y;
	t_coords	destination;

	destination.x = cos(data->player_ang * (M_PI / 180));
	destination.y = sin(data->player_ang * (M_PI / 180));
	target_x = (int)(data->player->x - (0.22 * destination.x));
	target_y = (int)(data->player->y - (0.22 * destination.y));
	if (data->map[target_y][target_x] != '1'
		&& data->map[target_y][(int)data->player->x] != '1'
		&& data->map[(int)data->player->y][target_x] != '1')
	{
		data->player->y -= 0.1 * destination.y;
		data->player->x -= 0.1 * destination.x;
	}
}

static void	move_up(t_data *data)
{
	int			target_x;
	int			target_y;
	t_coords	destination;

	destination.x = cos(data->player_ang * (M_PI / 180));
	destination.y = sin(data->player_ang * (M_PI / 180));
	target_x = (int)(data->player->x + (0.22 * destination.x));
	target_y = (int)(data->player->y + (0.22 * destination.y));
	if (data->map[target_y][target_x] != '1'
		&& data->map[target_y][(int)data->player->x] != '1'
		&& data->map[(int)data->player->y][target_x] != '1')
	{
		data->player->y += 0.1 * destination.y;
		data->player->x += 0.1 * destination.x;
	}
}

float	normalize_ang(float angle)
{
	angle = fmod(angle, 360);
	if (angle < 0)
		angle += 360;
	return (angle);
}

void	handle_keys(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		safe_exit(data, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_up(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_down(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player_ang = normalize_ang(data->player_ang - ROTATION_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player_ang = normalize_ang(data->player_ang + ROTATION_SPEED);
}
