/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:27:57 by okamili           #+#    #+#             */
/*   Updated: 2023/09/20 23:30:06 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_data	*init_data(void)
{
	t_data	*result;

	result = ft_calloc(1, sizeof(t_data));
	result->player = ft_calloc(1, sizeof(t_coords));
	result->player->x = -1;
	result->player->y = -1;
	result->east_path = NULL;
	result->west_path = NULL;
	result->north_path = NULL;
	result->south_path = NULL;
	result->colors = ft_calloc(3, sizeof(char *));
	result->map = NULL;
	return (result);
}
