/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:52:50 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 04:02:38 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_block(mlx_image_t *canvas, double point[2], long color)
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
			if ((location.x + col) / MINIMAP_SCALE > 0
				&& (location.x + col) / MINIMAP_SCALE < WIDTH
				&& (location.y + row) / MINIMAP_SCALE > 0
				&& (location.y + row) / MINIMAP_SCALE < HEIGHT)
				mlx_put_pixel(canvas, (location.x + col) / MINIMAP_SCALE,
					(location.y + row) / MINIMAP_SCALE, color);
		}
	}
}

void	draw_line(t_data *data, t_ray ray)
{
	float		step;
	int			i;
	t_coords	p1;
	t_coords	p2;
	t_coords	d;

	p1.x = data->player->x * BLOCK_SIZE;
	p1.y = data->player->y * BLOCK_SIZE;
	p2.x = ray.x;
	p2.y = ray.y;
	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	step = fabs(d.y);
	if (fabs(d.x) > fabs(d.y))
		step = fabs(d.x);
	i = -1;
	while (++i < step && step < INT_MAX)
	{
		if ((p1.x / MINIMAP_SCALE >= 0 && p1.x / MINIMAP_SCALE < WIDTH)
			&& (p1.y / MINIMAP_SCALE >= 0 && p1.y / MINIMAP_SCALE < HEIGHT))
			mlx_put_pixel(data->minimap_img, p1.x / MINIMAP_SCALE,
				p1.y / MINIMAP_SCALE, M_RAYS);
		p1.x += (d.x) / step;
		p1.y += (d.y) / step;
	}
}

void	draw_vue_angle(t_data *data)
{
	t_ray		ray;
	float		view_angle;
	float		step;
	int			i;

	view_angle = data->player_ang - 30;
	step = (60.0 / WIDTH);
	view_angle = normalize_ang(view_angle);
	draw_SkyAndFloor(data);
	i = -1;
	while (++i <= WIDTH)
	{
		ray = get_shortest_ray(data, view_angle);
		ray.distance = ray.distance
			* cos((view_angle - data->player_ang) * (M_PI / 180));
		draw_line(data, ray);
		draw_3d_wall(data, ray, i);
		view_angle += step;
		view_angle = normalize_ang(view_angle);
	}
}

void	draw_player(t_data *data)
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
				&& (player.x + point.y) / MINIMAP_SCALE > 0
				&& (player.x + point.y) / MINIMAP_SCALE < WIDTH
				&& (player.y + point.x) / MINIMAP_SCALE > 0
				&& (player.y + point.x) / MINIMAP_SCALE < HEIGHT)
				mlx_put_pixel(data->minimap_img, (player.x + point.x)
					/ MINIMAP_SCALE,
					(player.y + point.y) / MINIMAP_SCALE, M_PLYR);
		}
	}
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
	draw_vue_angle(data);
}
