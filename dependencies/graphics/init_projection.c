/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:06:13 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 00:41:42 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	mouse_rotation(double xpos, double ypos, void *param)
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
	data->player_ang = 360 - (start + ((xpos * 720) / WIDTH));
}

static void	iterate(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	handle_keys(data);
	mlx_cursor_hook(data->mlx, &mouse_rotation, data);
	draw_minimap(data);
}

void	init_projection(t_data *data)
{
	mlx_loop_hook(data->mlx, &iterate, data);
}
