/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vert_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:59:38 by nettalha          #+#    #+#             */
/*   Updated: 2023/09/19 04:34:57 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

t_ray get_vert_intersection(t_data *data, double angle)
{
	t_ray ray;
	double ystep, xstep;
	double wall_hit_x = 1000, wall_hit_y = 1000;
	int	depth;

	ray.is_facing_down = (angle > 0 && angle < 180);
	ray.is_facing_up = !ray.is_facing_down;
	ray.is_facing_right = (angle < 90 || angle > 270);
	ray.is_facing_left = !ray.is_facing_right;
	depth = 10000;
	if (angle == 90 || angle == 270)
	{
		wall_hit_x = 0;
		wall_hit_y = 0;
		depth = 0;
	}
	//

	t_coords temp_player;

	temp_player.x = data->player->x * BLOCK_SIZE;
	temp_player.y = data->player->y * BLOCK_SIZE;

	//

	ray.x = floor(temp_player.x / BLOCK_SIZE) * BLOCK_SIZE;
	if (ray.is_facing_right)
		ray.x += BLOCK_SIZE;
	if (ray.is_facing_left)
		ray.x -= 0.0001;
	//
	ray.y = temp_player.y + (ray.x - temp_player.x) * tan(angle * (M_PI / 180));
	//
	xstep = BLOCK_SIZE;
	if (ray.is_facing_left)
		xstep *= -1;
	//
	ystep = xstep * tan(angle * (M_PI / 180));

	//
	{
		double x_to_check;
		double y_to_check;
		int grid_x, grid_y;
		while (depth > 0 && ray.x >= 0 && ray.x < (data->map_w * BLOCK_SIZE) &&
			   ray.y >= 0 && ray.y < data->map_h * BLOCK_SIZE)
		{
			y_to_check = ray.y;
			x_to_check = ray.x;
			grid_x = floor(x_to_check / BLOCK_SIZE);
			grid_y = floor(y_to_check / BLOCK_SIZE);
			if (grid_x < 0 || grid_x >= data->map_w || grid_y < 0 || grid_y >= data->map_h)
				break;
			if (data->map[grid_y][grid_x] == '1')
			{
				wall_hit_x = ray.x;
				wall_hit_y = ray.y;
				break;
			}
			else
			{
				ray.x += xstep;
				ray.y += ystep;
			}
			depth--;
		}
	}
	ray.distance = sqrt(pow(ray.x - temp_player.x, 2) + pow(ray.y - temp_player.y, 2));
	// ray.x = wall_hit_x;
	// ray.y = wall_hit_y;
	return (ray);
}