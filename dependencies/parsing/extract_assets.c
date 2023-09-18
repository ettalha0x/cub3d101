/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:56:54 by okamili           #+#    #+#             */
/*   Updated: 2023/09/17 23:45:25 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	extract_textures(t_data *data, char *direction, char *asset)
{
	char	*tmp;

	tmp = direction;
	direction = ft_strtrim(tmp, " \t\v\r\f");
	free(tmp);
	tmp = asset;
	asset = ft_strtrim(tmp, " \t\v\r\f");
	free(tmp);
	if (!ft_strncmp(direction, "WE", 2))
		data->west_path = ft_strdup(asset);
	else if (!ft_strncmp(direction, "SO", 2))
		data->south_path = ft_strdup(asset);
	else if (!ft_strncmp(direction, "NO", 2))
		data->north_path = ft_strdup(asset);
	else if (!ft_strncmp(direction, "EA", 2))
		data->east_path = ft_strdup(asset);
	else if (!ft_strncmp(direction, "F", 2))
		data->colors[0] = ft_strdup(asset);
	else if (!ft_strncmp(direction, "C", 2))
		data->colors[1] = ft_strdup(asset);
	free(direction);
	free(asset);
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
		extract_textures(data, ft_substr(file_data[index], 0, 2),
			ft_substr(file_data[index], 2, ft_strlen(file_data[index])));
	extract_map(data, file_data);
}
