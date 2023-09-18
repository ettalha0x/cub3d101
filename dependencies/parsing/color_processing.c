/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:47:36 by okamili           #+#    #+#             */
/*   Updated: 2023/09/12 00:57:30 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	rgba(int red, int green, int blue)
{
	return (red << 24 | green << 16 | blue << 8 | 0x000000FF);
}

void	color_processing(t_data *data)
{
	char	**flr;
	char	**ceil;

	flr = ft_split(data->colors[0], ',');
	ceil = ft_split(data->colors[1], ',');
	data->floor = rgba(ft_atoi(flr[0]), ft_atoi(flr[1]), ft_atoi(flr[2]));
	data->ceiling = rgba(ft_atoi(ceil[0]), ft_atoi(ceil[1]), ft_atoi(ceil[2]));
	free2d(flr);
	free2d(ceil);
}
