/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:19:10 by okamili           #+#    #+#             */
/*   Updated: 2023/09/18 17:32:50 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	init_game(t_data *data, char *title)
{
	int	mini_w;
	int	mini_h;

	mini_w = data->map_w * BLOCK_SIZE;
	mini_h = data->map_h * BLOCK_SIZE;
	data->mlx = mlx_init(WIDTH, HEIGHT, title, true);
	data->game_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->minimap_img = mlx_new_image(data->mlx, mini_w, mini_h);
	mlx_image_to_window(data->mlx, data->game_img, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap_img, 0, 0);
}
