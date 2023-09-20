/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:06:13 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 23:33:30 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

float	normalize_ang(float angle)
{
	angle = fmod(angle, 360);
	if (angle < 0)
		angle += 360;
	return (angle);
}

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
	data->player_ang = (start + ((xpos * 360) / WIDTH));
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
