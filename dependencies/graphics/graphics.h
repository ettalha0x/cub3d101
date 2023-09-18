/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:52:55 by okamili           #+#    #+#             */
/*   Updated: 2023/09/18 17:45:55 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <math.h>
# include "../parsing/parsing.h"

# define WIDTH 1300
# define HEIGHT 800
# define BLOCK_SIZE 50
# define MINIMAP_SCALE 0.2
# define ROTATION_SPEED 3
# define M_WALL -1
# define M_FLOR -1836517121
# define M_PLYR -1
# define M_RAYS -1777
# define SlateGray 1887473919
# define RoyalBlue 1097458175
# define Tangerine 4289003775

void	init_game(t_data *data, char *title);
void	draw_minimap(t_data *data);
void	handle_keys(t_data *data);
void	prejection_3d(t_data *data);
void	get_textures(t_data *data);
void	init_projection(t_data *data);

// get intersections functions
t_ray get_horz_intersection(t_data *data, double angle);
t_ray get_vert_intersection(t_data *data, double angle);

#endif