/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 08:05:36 by okamili           #+#    #+#             */
/*   Updated: 2023/09/19 04:30:10 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	player_angle(char direction)
{
	if (direction == 'N')
		return (90);
	if (direction == 'S')
		return (270);
	if (direction == 'E')
		return (0);
	if (direction == 'W')
		return (180);
	print_err("%WUnable To Set Player Angle Defaulted To 0°.");
	return (0);
}

static void	set_player_data(t_data *data, int row, int colm)
{
	if (data->player->x == -1 && data->player->y == -1)
	{
		data->player->x = colm + 0.15;
		data->player->y = row + 0.15;
		data->player_ang = player_angle(data->map[row][colm]);
		data->map[row][colm] = '0';
		return ;
	}
	print_err("%EMultiple Players Detected.");
	safe_exit(data, 1);
}

void	extract_player(t_data *data)
{
	int	row;
	int	colm;

	row = -1;
	while (data->map && data->map[++row])
	{
		colm = -1;
		while (data->map[row] && data->map[row][++colm])
		{
			if (ft_strchr("NSEW", data->map[row][colm]))
				set_player_data(data, row, colm);
		}
	}
	if (data->player->x == -1 && data->player->y == -1)
	{
		print_err("%EUnable To Detect Any Player.");
		safe_exit(data, 1);
	}
}
