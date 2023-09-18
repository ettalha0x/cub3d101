/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:31:40 by okamili           #+#    #+#             */
/*   Updated: 2023/09/17 05:29:07 by nettalha         ###   ########.fr       */
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
	init_game(data, "DOOM - Boring Edition!!");
	get_textures(data);
	init_projection(data);
	mlx_loop(data->mlx);
	safe_exit(data, 0);
	return (0);
}
