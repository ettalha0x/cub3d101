/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_horz_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:59:27 by nettalha          #+#    #+#             */
/*   Updated: 2023/09/19 19:40:09 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

t_ray get_horz_intersection(t_data *data, double angle)
{
	t_ray ray;
	double ystep, xstep;
	double wall_hit_x = 1000, wall_hit_y = 1000;
	int	depth;

	t_coords temp_player;

	temp_player.x = data->player->x * BLOCK_SIZE;
	temp_player.y = data->player->y * BLOCK_SIZE;
	
	ray.is_facing_down = (angle > 0 && angle < 180);
	ray.is_facing_up = !ray.is_facing_down;
	ray.is_facing_right = (angle < 90 || angle > 270);
	ray.is_facing_left = !ray.is_facing_right;
	//
	depth = 10000;
	if(angle == 0 || angle == 180 || angle == 360)
	{
		wall_hit_x = 0;
		wall_hit_y = 0;
		depth = 0;
	}
	//
	ray.y = floor(temp_player.y / BLOCK_SIZE) * BLOCK_SIZE;
	if (ray.is_facing_down)
		ray.y += BLOCK_SIZE;
	if (ray.is_facing_up)
		ray.y -= 0.0001;
	//
	ray.x = temp_player.x + (ray.y - temp_player.y) / tan(angle * (M_PI / 180));
	//
	ystep = BLOCK_SIZE;
	if (ray.is_facing_up)
		ystep *= -1;
	//
	xstep = ystep / tan(angle * (M_PI / 180));
	//
	{
		int grid_x, grid_y;
		while (depth > 0 && ray.x >= 0 && ray.x < (data->map_w * BLOCK_SIZE)
			&& ray.y >= 0 && ray.y < (data->map_h * BLOCK_SIZE))
		{
			// printf("ok %d\n", depth);
			grid_x = floor(ray.x / BLOCK_SIZE);
			grid_y = floor(ray.y / BLOCK_SIZE);
			if (grid_y < 0 || grid_y >= data->map_h || grid_x < 0 || grid_x >= (int)ft_strlen(data->map[grid_y]))
				break;
			if (data->map[grid_y][grid_x] != '0')
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
	// printf("horz ray x: %f, y: %f, distance: %f\n", ray.x, ray.y, ray.distance);
	// exit(0);
	return (ray);
}
