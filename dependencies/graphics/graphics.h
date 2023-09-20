/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:52:55 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 09:18:45 by okamili          ###   ########.fr       */
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
# define M_FLOR 2006371327
# define M_PLYR -1
# define M_RAYS -1777

/**
 * @brief Initialize the MLX library and set up canvas
 * for both 3D and minimap projections.
 * 
 * @param data Pointer to a t_data struct.
 * @param title Title of the game.
 */
void	init_game(t_data *data, char *title);
/**
 * @brief Draw a minimap based on the map data.
 * 
 * @param data Pointer to a t_data struct.
 */
void	draw_minimap(t_data *data);
/**
 * @brief Process key actions based on user input.
 * 
 * @param data Pointer to a t_data struct.
 */
void	handle_keys(t_data *data);
/**
 * @brief Begin projecting the game onto the MLX canvas.
 * 
 * @param data Pointer to a t_data struct.
 */
void	init_projection(t_data *data);
/**
 * @brief Convert a negative angle to its positive equivalent
 * 
 * @param angle The angle value.
 * @return float The processed angle in the range [0°, 360°].
 */
float	normalize_ang(float angle);
/**
 * @brief Render the sky and floor on the MLX canvas
 * using colors specified in the map file.
 * 
 * @param data Pointer to a t_data struct.
 */
void	draw_sky_floor(t_data *data);
/**
 * @brief Draw a block on the MLX canvas at specified
 * coordinates with the given RGBA color.
 * 
 * @param canvas Pointer to the MLX canvas.
 * @param point Coordinates specifying the block's location.
 * @param color RGBA value representing the block's color.
 */
void	draw_block(mlx_image_t *canvas, double point[2], long color);

void	draw_line(t_data *data, t_ray ray);
void	draw_3d_wall(t_data *data, t_ray ray, float i);
void	draw_columns(t_data *data, t_coords p, float height, t_ray ray);
void	draw_textures(t_data *data, t_coords img, t_coords tex, float height, mlx_texture_t *texture);

t_ray	get_shortest_ray(t_data *data, float angle);
t_ray	get_horz_intersection(t_data *data, double angle);
t_ray	get_vert_intersection(t_data *data, double angle);
#endif