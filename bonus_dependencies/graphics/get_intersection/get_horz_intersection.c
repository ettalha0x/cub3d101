/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_horz_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:59:27 by nettalha          #+#    #+#             */
/*   Updated: 2023/09/20 23:00:19 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

static void	get_ray_distance(t_data *data, t_ray *ray, int depth, double angle)
{
	int		grid_x;
	int		grid_y;
	double	ystep;
	double	xstep;

	ystep = BLOCK_SIZE;
	if (ray->is_facing_up)
		ystep *= -1;
	xstep = ystep / tan(angle * (M_PI / 180));
	while (depth > 0 && ray->x >= 0 && ray->x < (data->map_w * BLOCK_SIZE)
		&& ray->y >= 0 && ray->y < (data->map_h * BLOCK_SIZE))
	{
		grid_x = floor(ray->x / BLOCK_SIZE);
		grid_y = floor(ray->y / BLOCK_SIZE);
		if (grid_y < 0 || grid_y >= data->map_h || grid_x < 0
			|| grid_x >= (int)ft_strlen(data->map[grid_y])
			|| data->map[grid_y][grid_x] != '0')
			break ;
		else
		{
			ray->x += xstep;
			ray->y += ystep;
		}
		depth--;
	}
}

t_ray	get_horz_intersection(t_data *data, double angle)
{
	t_ray		ray;
	int			depth;
	t_coords	temp_player;

	temp_player.x = data->player->x * BLOCK_SIZE;
	temp_player.y = data->player->y * BLOCK_SIZE;
	ray.is_facing_down = (angle > 0 && angle < 180);
	ray.is_facing_up = !ray.is_facing_down;
	ray.is_facing_right = (angle < 90 || angle > 270);
	ray.is_facing_left = !ray.is_facing_right;
	depth = data->map_w * data->map_h;
	if (angle == 0 || angle == 180 || angle == 360)
		depth = 0;
	ray.y = floor(temp_player.y / BLOCK_SIZE) * BLOCK_SIZE;
	if (ray.is_facing_down)
		ray.y += BLOCK_SIZE;
	if (ray.is_facing_up)
		ray.y -= 0.001;
	ray.x = temp_player.x + (ray.y - temp_player.y) / tan(angle * (M_PI / 180));
	get_ray_distance(data, &ray, depth, angle);
	ray.distance = sqrt(pow(ray.x - temp_player.x, 2)
			+ pow(ray.y - temp_player.y, 2));
	return (ray);
}
