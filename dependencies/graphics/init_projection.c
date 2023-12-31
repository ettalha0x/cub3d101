/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:06:13 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 23:33:00 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_vue_angle(t_data *data)
{
	t_ray		ray;
	float		view_angle;
	float		step;
	int			i;

	view_angle = data->player_ang - 30;
	step = (60.0 / WIDTH);
	view_angle = normalize_ang(view_angle);
	draw_sky_floor(data);
	i = -1;
	while (++i <= WIDTH)
	{
		ray = get_shortest_ray(data, view_angle);
		ray.distance = ray.distance
			* cos((view_angle - data->player_ang) * (M_PI / 180));
		draw_3d_wall(data, ray, i);
		view_angle += step;
		view_angle = normalize_ang(view_angle);
	}
}

float	normalize_ang(float angle)
{
	angle = fmod(angle, 360);
	if (angle < 0)
		angle += 360;
	return (angle);
}

static void	iterate(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	handle_keys(data);
	draw_vue_angle(data);
}

void	init_projection(t_data *data)
{
	mlx_loop_hook(data->mlx, &iterate, data);
}
