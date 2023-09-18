/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_horz_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:59:27 by nettalha          #+#    #+#             */
/*   Updated: 2023/09/18 17:16:17 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

t_ray get_horz_intersection(t_data *data, double angle)
{
	t_coords intercept;
	t_ray ray;
	double ystep, xstep;
	double wall_hit_x = INT_MAX, wall_hit_y = INT_MAX;

	t_coords temp_player;

	temp_player.x = data->player->x * BLOCK_SIZE;
	temp_player.y = data->player->y * BLOCK_SIZE;

	ray.is_facing_up = (angle > 0 && angle < 180);
	ray.is_facing_down = !ray.is_facing_up;
	ray.is_facing_right = (angle < 90 || angle > 270);
	ray.is_facing_left = !ray.is_facing_right;
	//
	intercept.y = floor(temp_player.y / BLOCK_SIZE) * BLOCK_SIZE;
	if (ray.is_facing_down)
		intercept.y += BLOCK_SIZE;
	if (ray.is_facing_up)
		intercept.y -= 0.0001;
	//
	intercept.x = temp_player.x + (intercept.y - temp_player.y) / tan(angle * (M_PI / 180));
	//
	ystep = BLOCK_SIZE;
	if (ray.is_facing_up)
		ystep *= -1;
	//
	xstep = BLOCK_SIZE / tan(angle * (M_PI / 180));
	if (ray.is_facing_left && (xstep > 0))
		xstep *= -1;
	if (ray.is_facing_right && (xstep < 0))
		xstep *= -1;
	//
	{
		double x_to_check;
		double y_to_check;
		int grid_x, grid_y;
		int safe = 0;
		while (intercept.x >= 0 && intercept.x < (data->map_w * BLOCK_SIZE) &&
			   intercept.y >= 0 && intercept.y < (data->map_h * BLOCK_SIZE)
			   && safe++ < 1024
			   )
		{
			x_to_check = intercept.x;
			y_to_check = intercept.y;
			grid_x = floor(x_to_check / BLOCK_SIZE);
			grid_y = floor(y_to_check / BLOCK_SIZE);
			if (grid_x < 0 || grid_x >= data->map_w || grid_y < 0 || grid_y >= data->map_h)
				break;
			if (data->map[grid_y][grid_x] != '0')
			{
				wall_hit_x = intercept.x;
				wall_hit_y = intercept.y;
				break;
			}
			else
			{
				intercept.x += xstep;
				intercept.y += ystep;
			}
		}
	}
	ray.distance = sqrt(pow(wall_hit_x - temp_player.x, 2) + pow(wall_hit_y - temp_player.y, 2));
	ray.x = wall_hit_x;
	ray.y = wall_hit_y;
	return (ray);
}
