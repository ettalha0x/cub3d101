/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:50:12 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 06:26:20 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	get_textures(t_data	*data)
{
	data->textures[0] = mlx_load_png(data->north_path);
	data->textures[1] = mlx_load_png(data->south_path);
	data->textures[2] = mlx_load_png(data->east_path);
	data->textures[3] = mlx_load_png(data->west_path);
	if (!data->textures[0] || !data->textures[1]
		|| !data->textures[2] || !data->textures[3])
	{
		print_err("%EError loading textures.");
		safe_exit(data, 1);
	}
}

void	draw_textures(t_data *data, t_coords img, t_coords tex, float height, mlx_texture_t *texture)
{
	int			x;
	int			x2;
	int			y2;
	uint32_t	y;
	uint8_t		*pixelx;
	uint8_t		*pixeli;

	x = tex.x;
	y = 0;
	x2 = img.x;
	y2 = img.y;
	if (height > data->game_img->height)
		y = (height - data->game_img->height) / 2;
	if (y2 < 0)
		y2 = 0;
	while (y2 < (int)data->game_img->height - 1 && y < height - 1)
	{
		tex.y = y * ((float) texture->height / (float) height);
		if (tex.y < texture->height
			&& (((int) tex.y * texture->width) + x) < texture->width * texture->height)
		{
			pixelx = &texture->pixels[(((int) tex.y * texture->width) + x) * texture->bytes_per_pixel];
			pixeli = &data->game_img->pixels[((y2 * (data->game_img->width)) + x2) * texture->bytes_per_pixel];
			ft_memmove(pixeli, pixelx, texture->bytes_per_pixel);
		}
		y2++;
		y++;
	}
}

void	draw_columns(t_data *data, t_coords p, float height, t_ray ray)
{
	t_coords		img;
	t_coords		tex;
	mlx_texture_t	*texture;
	float			width_ratio;

	img.x = p.x;
	img.y = p.y;
	if (ray.is_horz)
	{
		texture = data->textures[0];
		if (ray.is_facing_up)
			texture = data->textures[1];
		width_ratio = (float)((float)texture->width / (float) BLOCK_SIZE);
		tex.x = fmod(ray.x, BLOCK_SIZE) * (width_ratio);
	}
	else
	{
		texture = data->textures[2];
		if (ray.is_facing_left)
			texture = data->textures[3];
		width_ratio = (float)((float)texture->width / (float)BLOCK_SIZE);
		tex.x = fmod(ray.y, BLOCK_SIZE) * (width_ratio);
	}
	draw_textures(data, img, tex, height, texture);
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
