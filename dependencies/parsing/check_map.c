/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:12:25 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 06:30:07 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	get_textures(t_data	*data)
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

void	check_map(t_data *data, char *filename)
{
	char	**file_data;

	valid_name(data, filename);
	file_exist(data, filename);
	file_data = read_file(data, filename);
	extract_assets(data, file_data);
	free2d(file_data);
	refining_spaces(data);
	check_assets(data);
	check_terrain(data);
	extract_player(data);
	color_processing(data);
	get_textures(data);
}
