/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_terrain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 07:54:57 by okamili           #+#    #+#             */
/*   Updated: 2023/09/13 21:28:22 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_walled_off(t_data *data)
{
	int		row;
	int		colm;

	row = -1;
	while (data->map && data->map[++row])
	{
		colm = -1;
		while (data->map && data->map[row][++colm])
		{
			if (ft_strchr("0NSEW", data->map[row][colm]))
			{
				if (!row || !colm || row == (int)(data->map_h - 1)
					|| colm == (int)(data->map_w - 1))
					return (0);
				if (ft_strchr(" \0", data->map[row + 1][colm])
					|| ft_strchr(" \0", data->map[row - 1][colm])
					|| ft_strchr(" \0", data->map[row][colm - 1])
					|| ft_strchr(" \0", data->map[row][colm + 1]))
					return (0);
			}
		}
	}
	return (1);
}

void	check_terrain(t_data *data)
{
	int	row;
	int	colm;

	row = -1;
	while (data->map && data->map[++row])
	{
		colm = -1;
		while (data->map[row] && data->map[row][++colm])
		{
			if (!ft_strchr(" 01NSEW", data->map[row][colm]))
			{
				print_err("%EInvalid Map Character.");
				if (data->map[row][colm] == '\t')
					print_err("%ITab Detected on map line %d.", row);
				safe_exit(data, 1);
			}
		}
	}
	if (!is_walled_off(data))
	{
		print_err("%EMap Must Be Enclosed By Walls.");
		safe_exit(data, 1);
	}
}
