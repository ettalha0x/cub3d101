/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:18:58 by okamili           #+#    #+#             */
/*   Updated: 2023/09/18 00:07:47 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	repeated_textures(t_data *data, char **names)
{
	if (!names[0] || !names[1]
		|| !names[2] || !names[3])
	{
		print_err("%EMissing Texture Declaration Within The Map.");
		free2d(names);
		safe_exit(data, 1);
	}
	if (!ft_strncmp(names[0], names[1], 9999)
		|| !ft_strncmp(names[0], names[2], 9999)
		|| !ft_strncmp(names[0], names[3], 9999)
		|| !ft_strncmp(names[1], names[2], 9999)
		|| !ft_strncmp(names[1], names[3], 9999)
		|| !ft_strncmp(names[2], names[3], 9999))
	{
		print_err("%EEnsure Unique Textures Per Wall Direction.");
		free2d(names);
		safe_exit(data, 1);
	}
	free2d(names);
}

static void	textures_format(t_data *data)
{
	int		index;
	char	*extention;
	char	**format;

	format = ft_calloc(5, sizeof(char *));
	extention = ".png";
	format[0] = ft_substr(data->north_path, ft_strlen(data->north_path) - 4, 4);
	format[1] = ft_substr(data->south_path, ft_strlen(data->south_path) - 4, 4);
	format[2] = ft_substr(data->east_path, ft_strlen(data->east_path) - 4, 4);
	format[3] = ft_substr(data->west_path, ft_strlen(data->west_path) - 4, 4);
	index = -1;
	while (++index < 4)
	{
		if (ft_strncmp(extention, format[index], 4))
		{
			if (ft_strchr(" \t\n", format[index][0]))
				print_err("%EMissing Texture Path.");
			else
				print_err("%ETextures Extension Must Be %s", extention);
			free2d(format);
			safe_exit(data, 1);
		}
	}
	free2d(format);
}

static void	textures_exist(t_data *data)
{
	int	fd[4];

	fd[0] = open(data->north_path, O_RDONLY);
	fd[1] = open(data->south_path, O_RDONLY);
	fd[2] = open(data->east_path, O_RDONLY);
	fd[3] = open(data->west_path, O_RDONLY);
	if (read(fd[0], 0, 0) || read(fd[1], 0, 0)
		|| read(fd[2], 0, 0) || read(fd[3], 0, 0))
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
		close(fd[3]);
		print_err("%EUnable To Open Textures Path.");
		print_err("%IProviding An Absolute Path Can Help Solve The Issue.");
		safe_exit(data, 1);
	}
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
}

static void	check_rgb(t_data *data, char *color)
{
	int		index;
	char	**rgb;

	index = -1;
	rgb = ft_split(color, ',');
	while (color && rgb[++index])
	{
		if (ft_atoi(rgb[index]) < 0 || ft_atoi(rgb[index]) > 255)
		{
			free2d(rgb);
			print_err("%EInvalid RGB Color.");
			safe_exit(data, 1);
		}
	}
	if (!color || !index || index != 3)
	{
		free2d(rgb);
		if (!index || index < 0)
			print_err("%EMissing RGB Value.");
		else
			print_err("%EInvalid RGB Color.");
		safe_exit(data, 1);
	}
	free2d(rgb);
}

void	check_assets(t_data *data)
{
	int		index;
	int		texture;
	char	**temp;
	char	**result;

	result = ft_calloc(5, sizeof(char *));
	result[0] = data->north_path;
	result[1] = data->south_path;
	result[2] = data->east_path;
	result[3] = data->west_path;
	texture = -1;
	while (result[++texture])
	{
		temp = ft_split(result[texture], '/');
		index = 0;
		while (temp[index])
			index++;
		result[texture] = ft_strdup(temp[--index]);
		free2d(temp);
	}
	repeated_textures(data, result);
	textures_format(data);
	textures_exist(data);
	check_rgb(data, data->colors[0]);
	check_rgb(data, data->colors[1]);
}
