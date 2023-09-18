/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:51:58 by okamili           #+#    #+#             */
/*   Updated: 2023/09/13 20:26:35 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	valid_name(t_data *data, char *filename)
{
	char	*format;

	format = ft_substr(filename, ft_strlen(filename) - 4, 4);
	if (ft_strncmp(".cub", format, 4))
	{
		free(format);
		print_err("%EInvalid Map Extension.");
		safe_exit(data, 1);
	}
	free(format);
}
