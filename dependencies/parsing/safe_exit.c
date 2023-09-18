/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:24:41 by okamili           #+#    #+#             */
/*   Updated: 2023/09/18 17:33:45 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_textures(t_data *data)
{
	if (data->textures[0])
		mlx_delete_texture(data->textures[0]);
	if (data->textures[1])
		mlx_delete_texture(data->textures[1]);
	if (data->textures[2])
		mlx_delete_texture(data->textures[2]);
	if (data->textures[3])
		mlx_delete_texture(data->textures[3]);
}

void	safe_exit(t_data *data, int exit_code)
{
	if (data->mlx)
	{
		mlx_delete_image(data->mlx, data->game_img);
		mlx_delete_image(data->mlx, data->minimap_img);
		mlx_terminate(data->mlx);
	}
	free_textures(data);
	free(data->north_path);
	free(data->west_path);
	free(data->east_path);
	free(data->south_path);
	free(data->player);
	free2d(data->colors);
	free2d(data->map);
	free(data);
	exit(exit_code);
}
