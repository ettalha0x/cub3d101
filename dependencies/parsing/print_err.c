/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:40:16 by okamili           #+#    #+#             */
/*   Updated: 2023/09/13 20:56:26 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdarg.h>

static void	print_char(char letter)
{
	if (letter)
		write(2, (char [2]){letter, '\0'}, 1);
}

static void	print_str(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}

static void	print_num(int num)
{
	if (num == -2147483648)
	{
		print_str("-2147483648");
		return ;
	}
	if (num < 0)
	{
		num *= -1;
		print_char('-');
	}
	if (num < 10)
		print_char(num + '0');
	else
	{
		print_num(num / 10);
		print_num(num % 10);
	}
}

static void	type_handler(char letter, va_list args)
{
	if (letter == 'c')
		print_char(va_arg(args, int));
	else if (letter == 's')
		print_str(va_arg(args, char *));
	else if (letter == 'd')
		print_num(va_arg(args, int));
	else if (letter == 'E')
		print_str("\033[1;31mERROR\033[1;0m:\n");
	else if (letter == 'W')
		print_str("\033[1;33mWARNING\033[1;0m:\n");
	else if (letter == 'I')
		print_str("\033[1;34mINFO\033[1;0m:\n");
}

void	print_err(char *str, ...)
{
	int		index;
	va_list	args;

	index = -1;
	va_start(args, str);
	while (str && str[++index])
	{
		if (str[index] == '%')
			type_handler(str[++index], args);
		else
			print_char(str[index]);
	}
	print_char('\n');
}
