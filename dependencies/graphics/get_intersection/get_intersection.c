/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okamili <okamili@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:17:35 by nettalha          #+#    #+#             */
/*   Updated: 2023/09/20 00:50:27 by okamili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

t_ray	copy_ray(t_ray ray, int is_horz)
{
	t_ray	new_ray;

	new_ray.distance = ray.distance;
	new_ray.is_horz = is_horz;
	new_ray.x = ray.x;
	new_ray.y = ray.y;
	new_ray.is_facing_down = ray.is_facing_down;
	new_ray.is_facing_up = ray.is_facing_up;
	new_ray.is_facing_left = ray.is_facing_left;
	new_ray.is_facing_right = ray.is_facing_right;
	return (new_ray);
}

t_ray	get_shortest_ray(t_data *data, float angle)
{
	t_ray	hor_ray;
	t_ray	ver_ray;
	t_ray	shortest_ray;

	hor_ray = get_horz_intersection(data, angle);
	ver_ray = get_vert_intersection(data, angle);
	if (hor_ray.distance < ver_ray.distance)
		shortest_ray = copy_ray(hor_ray, 1);
	else
		shortest_ray = copy_ray(ver_ray, 0);
	return (shortest_ray);
}
