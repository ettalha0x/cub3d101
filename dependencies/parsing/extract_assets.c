/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:56:54 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 08:12:59 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	assign_path(char **destination, char *asset)
{
	if (*destination)
		return (1);
	*destination = ft_strdup(asset);
	return (0);
}

static int	extract_textures(t_data *data, char *direction, char *asset)
{
	int		err;
	char	*tmp;

	tmp = direction;
	direction = ft_strtrim(tmp, " \t\v\r\f");
	free(tmp);
	tmp = asset;
	asset = ft_strtrim(tmp, " \t\v\r\f");
	free(tmp);
	err = 0;
	if (!ft_strncmp(direction, "WE", 2))
		err = assign_path(&data->west_path, asset);
	else if (!ft_strncmp(direction, "SO", 2))
		err = assign_path(&data->south_path, asset);
	else if (!ft_strncmp(direction, "NO", 2))
		err = assign_path(&data->north_path, asset);
	else if (!ft_strncmp(direction, "EA", 2))
		err = assign_path(&data->east_path, asset);
	else if (!ft_strncmp(direction, "F", 2))
		err = assign_path(&data->colors[0], asset);
	else if (!ft_strncmp(direction, "C", 2))
		err = assign_path(&data->colors[1], asset);
	free(direction);
	free(asset);
	return (err);
}

static void	extract_map(t_data *data, char **file_data)
{
	int	index;

	index = 5;
	data->map_w = 0;
	data->map = ft_calloc((data->map_h + 1), sizeof(char *));
	while (file_data[++index])
	{
		data->map[index - 6] = ft_strdup(file_data[index]);
		if (data->map_w < (int)ft_strlen(data->map[index - 6]))
			data->map_w = ft_strlen(data->map[index - 6]);
	}
}

void	extract_assets(t_data *data, char **file_data)
{
	int	index;

	index = -1;
	while (++index < 6)
	{
		if (extract_textures(data, ft_substr(file_data[index], 0, 2),
				ft_substr(file_data[index], 2, ft_strlen(file_data[index]))))
		{
			free2d(file_data);
			print_err("%EDuplicate Texture Declaration.");
			safe_exit(data, 1);
		}
	}
	extract_map(data, file_data);
}
