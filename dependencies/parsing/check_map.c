/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:12:25 by okamili           #+#    #+#             */
/*   Updated: 2023/09/13 21:25:56 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
}
