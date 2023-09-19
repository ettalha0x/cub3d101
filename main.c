/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:31:40 by okamili           #+#    #+#             */
/*   Updated: 2023/09/19 23:28:55 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies/parsing/parsing.h"
#include "dependencies/graphics/graphics.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		print_err("%EInvalid Number Of Arguments.");
		exit(1);
	}
	data = init_data();
	check_map(data, argv[1]);
	get_textures(data);
	init_game(data, "DOOM - Boring Edition!!");
	init_projection(data);
	mlx_loop(data->mlx);
	safe_exit(data, 0);
	return (0);
}
