/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:06:13 by okamili           #+#    #+#             */
/*   Updated: 2023/09/18 17:22:59 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void moose(double xpos, double ypos, void* param)
{
	t_data			*data;
	static float	start;
	static int		lock;

	(void) ypos;
	data = (t_data *)param;
	if (!lock)
	{
		start = data->player_ang;
		lock = 1;
	}
	data->player_ang = 360 - (start + ((xpos * 720)/1150));
}

static void	iterate(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	handle_keys(data);
	// prejection_3d(data);
	mlx_cursor_hook(data->mlx, &moose, data);
	draw_minimap(data);
}

void	init_projection(t_data *data)
{
	mlx_loop_hook(data->mlx, &iterate, data);
}
