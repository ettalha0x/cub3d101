/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:50:12 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 12:44:29 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	init_points(t_int_coords *p1, t_int_coords *p2, t_two_coords *twin)
{
	p1->x = twin->tex.x;
	p1->y = -1;
	p2->x = twin->img.x;
	p2->y = twin->img.y - 1;
}

void	draw_text(t_data *data, t_two_coords twin, float h, mlx_texture_t *tex)
{
	t_int_coords	p1;
	t_int_coords	p2;
	uint8_t			*px;
	uint8_t			*pi;

	init_points(&p1, &p2, &twin);
	if (h > data->game_img->height)
		p1.y = (h - data->game_img->height) / 2;
	if (p2.y < 0)
		p2.y = 0;
	while (++p2.y < (int)data->game_img->height - 1 && ++p1.y < h - 1)
	{
		twin.tex.y = p1.y * ((float) tex->height / (float) h);
		if (twin.tex.y < tex->height
			&& (twin.tex.y * tex->width + p1.x) < tex->width * tex->height)
		{
			px = &tex->pixels
			[(((int)twin.tex.y * tex->width) + p1.x) * tex->bytes_per_pixel];
			pi = &data->game_img->pixels
			[((p2.y * (data->game_img->width)) + p2.x) * tex->bytes_per_pixel];
			ft_memmove(pi, px, tex->bytes_per_pixel);
		}
	}
}

void	draw_columns(t_data *data, t_coords p, float height, t_ray ray)
{
	t_two_coords	twin;
	mlx_texture_t	*texture;
	float			width_ratio;

	twin.img.x = p.x;
	twin.img.y = p.y;
	if (ray.is_horz)
	{
		texture = data->textures[0];
		if (ray.is_facing_up)
			texture = data->textures[1];
		width_ratio = (float)((float)texture->width / (float) BLOCK_SIZE);
		twin.tex.x = fmod(ray.x, BLOCK_SIZE) * (width_ratio);
	}
	else
	{
		texture = data->textures[2];
		if (ray.is_facing_left)
			texture = data->textures[3];
		width_ratio = (float)((float)texture->width / (float)BLOCK_SIZE);
		twin.tex.x = fmod(ray.y, BLOCK_SIZE) * (width_ratio);
	}
	draw_text(data, twin, height, texture);
}

void	draw_3d_wall(t_data *data, t_ray ray, float i)
{
	t_coords	p;

	p.x = i;
	p.y = ((HEIGHT / 2) - (((HEIGHT / 2) * 50) / ray.distance));
	draw_columns(data, p, HEIGHT - (p.y * 2), ray);
}

void	draw_sky_floor(t_data *data)
{
	float	i;
	float	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if (i > HEIGHT / 2)
				mlx_put_pixel(data->game_img, j, i, data->floor);
			else
				mlx_put_pixel(data->game_img, j, i, data->ceiling);
		}
	}
}
