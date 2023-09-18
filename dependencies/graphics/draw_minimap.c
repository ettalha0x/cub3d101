/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:52:50 by okamili           #+#    #+#             */
/*   Updated: 2023/09/18 17:39:59 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	draw_block(mlx_image_t *canvas, double point[2], long color)
{
	int			col;
	int			row;
	t_coords	location;

	location.x = point[0] * BLOCK_SIZE;
	location.y = point[1] * BLOCK_SIZE;
	row = -1;
	while (++row < BLOCK_SIZE)
	{
		col = -1;
		while (++col < BLOCK_SIZE)
		{
			if (!col || !row)
				mlx_put_pixel(canvas, (location.x + col),
					(location.y + row), 841372671);
			else
				mlx_put_pixel(canvas, (location.x + col),
					(location.y + row), color);
		}
	}
}

static void	draw_line(t_data *data, float angle)
{
	float			step;
	t_coords	plyr;
	t_coords	dist;

	plyr.x = data->player->x * BLOCK_SIZE;
	plyr.y = data->player->y * BLOCK_SIZE;
	dist.x = cos(angle * (M_PI / 180)) * (BLOCK_SIZE * data->map_w);
	dist.y = -sin(angle * (M_PI / 180)) * (BLOCK_SIZE * data->map_w);
	step = fabs(dist.y);
	if (fabs(dist.x) > fabs(dist.y))
		step = fabs(dist.x);
	while (true)
	{
		 if(((plyr.y/BLOCK_SIZE) > 0 && (plyr.x/BLOCK_SIZE) > 0
			&& data->map[(int)(plyr.y/BLOCK_SIZE)][(int)(plyr.x/BLOCK_SIZE)] == '1')
			|| data->map[(int)(plyr.y/BLOCK_SIZE)][(int)(plyr.x/BLOCK_SIZE)] == ' ')
			break;
        plyr.x += (dist.x / step);
        plyr.y += (dist.y / step);
		if (data->map[(int)((plyr.y + dist.y / step) / BLOCK_SIZE)][(int)(plyr.x / BLOCK_SIZE)] == '1'
			&& data->map[(int)(plyr.y / BLOCK_SIZE)][(int)((plyr.x + dist.x / step) / BLOCK_SIZE)] == '1')
			break ;
		mlx_put_pixel(data->minimap_img, plyr.x, plyr.y, M_RAYS);
	}
}

void	draw_vue_angle(t_data *data)
{
	data->vue_angle = (int)(data->player_ang - 30);
	while (data->vue_angle <= data->player_ang + 30)
	{
		draw_line(data, data->vue_angle);
		data->vue_angle += 0.1;
	}
}

static void	draw_player(t_data *data)
{
	int			ray;
	t_coords	point;
	t_coords	player;

	ray = BLOCK_SIZE / 7;
	player.x = (data->player->x * BLOCK_SIZE);
	player.y = (data->player->y * BLOCK_SIZE);
	point.y = -ray - 1;
	while (++point.y <= ray)
	{
		point.x = -ray - 1;
		while (++point.x <= ray)
		{
			if (pow(point.x, 2) + pow(point.y, 2) <= pow(ray, 2)
				&& (player.x + point.y) > 0 && (player.x + point.y) < data->map_w * BLOCK_SIZE
				&& (player.y + point.x) > 0 && (player.y + point.x) < data->map_h * BLOCK_SIZE)
				mlx_put_pixel(data->minimap_img, (player.x + point.x), (player.y + point.y), M_PLYR);
		}
	}
	draw_vue_angle(data);
}

void	draw_minimap(t_data *data)
{
	int	col;
	int	row;
	int	row_len;

	row = -1;
	while (data->map[++row])
	{
		col = -1;
		row_len = ft_strlen(data->map[row]);
		while (++col < data->map_w)
		{
			if ((col < row_len) && (data->map[row][col] == '1'))
				draw_block(data->minimap_img, (double [2]){col, row}, M_WALL);
			else if ((col < row_len) && ft_strchr("0NSEW", data->map[row][col]))
				draw_block(data->minimap_img, (double [2]){col, row}, M_FLOR);
		}
	}
	draw_player(data);
}
