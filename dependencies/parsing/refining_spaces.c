/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refining_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:57:33 by okamili           #+#    #+#             */
/*   Updated: 2023/09/12 13:40:31 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	common_spaces(t_data *data)
{
	size_t	row;
	size_t	count;
	size_t	result;

	row = -1;
	result = data->map_w;
	while (++row < (size_t)data->map_h)
	{
		count = 0;
		while (data->map[row])
		{
			if (data->map[row][count] == ' ')
				count++;
			else
				break ;
		}
		if (count < result)
			result = count;
	}
	return (result);
}

static size_t	row_len(size_t start, char *row)
{
	size_t	index;
	size_t	result;

	index = start;
	result = start;
	while (row && row[index] == ' ')
		index++;
	result = index;
	while (row && row[index])
	{
		if (ft_strchr("01NSEW", row[index]))
			result = index;
		index++;
	}
	return (++result - start);
}

static size_t	updated_width(char **map)
{
	size_t	row;
	size_t	temp;
	size_t	result;

	row = -1;
	result = 0;
	while (map[++row])
	{
		temp = ft_strlen(map[row]);
		if (temp > result)
			result = temp;
	}
	return (result);
}

void	refining_spaces(t_data *data)
{
	size_t	row;
	size_t	start;
	char	*temp;

	row = -1;
	start = common_spaces(data);
	while (data->map[++row])
	{
		temp = data->map[row];
		data->map[row] = ft_substr(temp, start, row_len(start, temp));
		free(temp);
	}
	data->map_w = updated_width(data->map);
}
