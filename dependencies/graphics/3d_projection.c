/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:50:12 by okamili           #+#    #+#             */
/*   Updated: 2023/09/19 09:08:43 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

unsigned int get_rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// int	isRayHorizontal(t_ray ray)
// {
//     float nearestX = ceilf(ray.x / 50) * 50;

//     float nearestY = ceilf(ray.y / 50) * 50;

//     if (fabs(ray.x - nearestX) <= 1.0)
//         ray.x = nearestX;

//     if (fabs(ray.y - nearestY) <= 1.0)
//         ray.y = nearestY;

//     if ((int)ray.y % 50 == 0)
//         return 1;
//     return 0;
// }

// static t_ray	get_ray_distance(t_data *data, t_coords p1, t_coords p2)
// {
// 	int			i;
// 	float		step;
// 	t_coords	d;
// 	t_ray		ray;

// 	i = -1;
// 	d.x = p2.x - p1.x;
// 	d.y = p2.y - p1.y;
// 	if (fabs(d.x) > fabs(d.y)) 
// 		step = fabs(d.x);
// 	else 
//     	step = fabs(d.y);
// 	while(++i <= step)
// 	{
// 	   if(((p1.y/BLOCK_SIZE) > 0 && (p1.x/BLOCK_SIZE) > 0
// 			&& data->map[(int)(p1.y/BLOCK_SIZE)][(int)(p1.x/BLOCK_SIZE)] == '1')
// 			|| data->map[(int)(p1.y/BLOCK_SIZE)][(int)(p1.x/BLOCK_SIZE)] == ' ')
// 			break;
//         p1.x += (d.x / step);
//         p1.y += (d.y / step);
// 		if ((data->map[(int)((p1.y + d.y / step)/BLOCK_SIZE)][(int)(p1.x/BLOCK_SIZE)] == '1'
// 			&& data->map[(int)(p1.y/BLOCK_SIZE)][(int)((p1.x + d.x / step)/BLOCK_SIZE)] == '1'))
// 			break;
//     }
// 	ray.x = p1.x;
// 	ray.y = p1.y;
// 	ray.is_horz = isRayHorizontal(ray);
// 	ray.distance = sqrt(pow(p1.x - (data->player->x * BLOCK_SIZE), 2) + pow(p1.y - (data->player->y * BLOCK_SIZE), 2));
// 	return (ray);
// }


void	get_textures(t_data	*data)
{
	data->textures[0] = mlx_load_png(data->north_path);
	data->textures[1] = mlx_load_png(data->south_path);
	data->textures[2] = mlx_load_png(data->east_path);
	data->textures[3] = mlx_load_png(data->west_path);
	if (!data->textures[0] || !data->textures[1] || !data->textures[2] || !data->textures[3])
		print_err("%EError loading textures.");
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
    {
        y = (height - data->game_img->height) / 2;
    }
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

void draw_columns(t_data *data, t_coords p, float height, t_ray ray)
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
        width_ratio = (float) ((float)texture->width / (float) BLOCK_SIZE);
        tex.x = fmod(ray.x , BLOCK_SIZE) * (width_ratio);
    }
	else
    {
		texture = data->textures[2];
        if (ray.is_facing_left)
            texture = data->textures[3];
        width_ratio = (float)((float)texture->width / (float)BLOCK_SIZE);
        tex.x = fmod(ray.y , BLOCK_SIZE) * (width_ratio);
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


void draw_SkyAndFloor(t_data *data)
{
	float	i;
	float	j;
	
	i = -1;
    while (++i < HEIGHT)
    {
		j = -1;
        while (++j < WIDTH)
        {
			if(i > HEIGHT / 2)
            	mlx_put_pixel(data->game_img, j, i, data->floor);
			else
				mlx_put_pixel(data->game_img, j, i, data->ceiling);
        }
    }
}

// void	prejection_3d(t_data *data)
// {
// 	int			i;
// 	t_ray		ray;
// 	t_coords	p1;
// 	t_coords	p2;
// 	float		width;

// 	width = data->map_w * BLOCK_SIZE;
// 	i = 0;
// 	data->vue_angle = (data->player_ang + 30) * (M_PI / 180);
// 	draw_SkyAndFloor(data);
// 	while (i < width)
// 	{
// 		p1.x = data->player->x * BLOCK_SIZE;
// 		p1.y = data->player->y * BLOCK_SIZE;
// 		p2.x = p1.x + cos(data->vue_angle) * width;	
// 		p2.y = p1.y - sin(data->vue_angle) * width;
// 		ray = get_ray_distance(data, p1, p2);
// 		ray.distance = ray.distance * cos(data->vue_angle - (data->player_ang * (M_PI / 180)));
// 		ray.is_facing_down = (data->vue_angle > 0 && data->vue_angle < 180 * (M_PI / 180));
// 		ray.is_facing_up = !ray.is_facing_down;
// 		ray.is_facing_right = (data->vue_angle < 90 * (M_PI / 180)|| data->vue_angle > 270 * (M_PI / 180));
// 		ray.is_facing_left = !ray.is_facing_right;
// 		draw_3d_wall(data, ray, i);
// 		data->vue_angle -= ((60  * (M_PI / 180)) / width);
// 		i++;
// 	}
// }
