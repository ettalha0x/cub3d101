/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:00:04 by okamili           #+#    #+#             */
/*   Updated: 2023/09/13 20:24:45 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	file_exist(t_data *data, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (read(fd, 0, 0))
	{
		print_err("%EFile Does Not Exist.");
		safe_exit(data, 1);
	}
	close (fd);
}
