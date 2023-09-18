/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:37:38 by okamili           #+#    #+#             */
/*   Updated: 2023/09/13 21:25:33 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	row_num(char *filename)
{
	int		fd;
	int		rows;
	char	*tmp0;
	char	*tmp1;

	rows = 0;
	fd = open(filename, O_RDONLY);
	tmp0 = get_next_line(fd);
	while (tmp0)
	{
		tmp1 = ft_strtrim(tmp0, " \n\t\v\r\f");
		free(tmp0);
		if (ft_strlen(tmp1))
			rows++;
		free(tmp1);
		tmp0 = get_next_line(fd);
	}
	close(fd);
	return (rows);
}

static void	extract_data(int fd, char **result)
{
	int		index;
	char	*tmp[2];

	index = 0;
	tmp[0] = get_next_line(fd);
	while (tmp[0])
	{
		tmp[1] = ft_strtrim(tmp[0], " \n\t\v\r\f");
		if (ft_strlen(tmp[1]))
			result[index++] = ft_strtrim(tmp[0], "\n");
		free(tmp[0]);
		free(tmp[1]);
		tmp[0] = get_next_line(fd);
	}
}

char	**read_file(t_data *data, char *filename)
{
	int		fd;
	char	**result;

	data->map_h = row_num(filename) - 6;
	if (data->map_h < 0)
	{
		print_err("%EEmpty Map File or Incorrect Map Data.");
		safe_exit(data, 1);
	}
	fd = open(filename, O_RDONLY);
	result = ft_calloc((data->map_h + 7), sizeof(char *));
	extract_data(fd, result);
	close(fd);
	return (result);
}
