/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:52:55 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 00:43:04 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <math.h>
# include <stdio.h>
# include "../parsing/parsing.h"

# define WIDTH 1300
# define HEIGHT 800
# define BLOCK_SIZE 50
# define MINIMAP_SCALE 6
# define ROTATION_SPEED 6
# define M_WALL -1
# define M_FLOR -1836517121
# define M_PLYR -1
# define M_RAYS -1777

void	init_game(t_data *data, char *title);
void	draw_minimap(t_data *data);
void	handle_keys(t_data *data);
void	init_projection(t_data *data);
float	normalize_ang(float angle);

t_ray	get_shortest_ray(t_data *data, float angle);
t_ray	get_horz_intersection(t_data *data, double angle);
t_ray	get_vert_intersection(t_data *data, double angle);

void	get_textures(t_data *data);
void	draw_line(t_data *data, t_ray ray, float angle);
void	draw_block(mlx_image_t *canvas, double point[2], long color);
void	draw_3d_wall(t_data *data, t_ray ray, float i);
void	draw_SkyAndFloor(t_data *data);
void	draw_columns(t_data *data, t_coords p, float height, t_ray ray);
void	draw_textures(t_data *data, t_coords img, t_coords tex, float height, mlx_texture_t *texture);
unsigned int	get_rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

#endif