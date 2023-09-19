/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:35:30 by okamili           #+#    #+#             */
/*   Updated: 2023/09/18 23:54:14 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include "../packages/libft/libft.h"
# include "../packages/MLX/minilibx.h"
# include "../packages/gnl/get_next_line.h"

typedef struct point_coordinates
{
	float	x;
	float	y;
}	t_coords;

typedef struct s_ray
{
	float	x;
	float	y;
	float	distance;
	float	is_horz;
	int		is_facing_down;
	int		is_facing_up;
	int		is_facing_right;
	int		is_facing_left;
}	t_ray;

typedef struct meta_data
{
	mlx_t			*mlx;
	mlx_image_t		*game_img;
	mlx_image_t		*minimap_img;

	t_coords		*player;
	float			player_ang;

	char			**map;
	int				map_w;
	int				map_h;

	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	char			**colors;

	mlx_texture_t	*textures[4];

	int				floor;
	int				ceiling;
}	t_data;

/**
 * @brief Initialize a t_data struct and return a pointer to it.
 *
 * @return Pointer to the initialized struct.
 */
t_data	*init_data(void);
/**
 * @brief Safely exits the program, freeing allocated data.
 * 
 * @param data Pointer to a t_data pointer.
 * @param exit_code Program exit value.
 */
void	safe_exit(t_data *data, int exit_code);
/**
 * @brief Check the validity of map assets and terrain.
 * 
 * @param data Pointer to a t_data struct.
 * @param filename Path to the map file.
 */
void	check_map(t_data *data, char *filename);
/**
 * @brief Check if the file at the given path is a .cub file.
 * 
 * @param data Pointer to a t_data struct.
 * @param filename Path to the map file.
 */
void	valid_name(t_data *data, char *filename);
/**
 * @brief Check if the map file path exists.
 * 
 * @param data Pointer to a t_data struct.
 * @param filename Path to the map file.
 */
void	file_exist(t_data *data, char *filename);
/**
 * @brief Read the content of the map file.
 * 
 * @param data Pointer to a t_data struct.
 * @param filename Path to the map file.
 * @return char** 2D array with the file's data.
 */
char	**read_file(t_data *data, char *filename);
/**
 * @brief Extract game assets into the t_data struct.
 * 
 * @param data Pointer to a t_data struct.
 * @param file_data 2D array containing map file data.
 */
void	extract_assets(t_data *data, char **file_data);
/**
 * @brief Validate game assets.
 * 
 * @param data Pointer to a t_data struct.
 */
void	check_assets(t_data *data);
/**
 * @brief Validate map components.
 * 
 * @param data Pointer to a t_data struct.
 */
void	check_terrain(t_data *data);
/**
 * @brief Extract player coordinates and direction.
 * 
 * @param data Pointer to a t_data struct.
 */
void	extract_player(t_data *data);
/**
 * @brief Validate and convert RGB values to RGBA.
 * 
 * @param data Pointer to a t_data struct.
 */
void	color_processing(t_data *data);
/**
 * @brief Remove leading and trailing spaces
 * from the map for accurate dimensions.
 * 
 * @param data Pointer to a t_data struct.
 */
void	refining_spaces(t_data *data);
/**
 * @brief Print a formatted error message to stderr
 * with custom formatting flags:
 * 
 * @note %c  = Character argument
 * @note %s  = String argument
 * @note %d  = Integer argument
 * @note %E  = ERROR (in red)
 * @note %I  = INFO (in blue)
 * @note %W  = WARNING (in yellow)
 * 
 * @param str The error message format string.
 * @param ... Arguments to be formatted and printed.
 */
void	print_err(char *str, ...);
/**
 * @brief Free a 2D array.
 * 
 * @param ptr Pointer to the 2D array.
 */
void	free2d(char **ptr);

#endif