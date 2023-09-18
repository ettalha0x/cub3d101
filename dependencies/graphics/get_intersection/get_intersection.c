/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:17:35 by nettalha          #+#    #+#             */
/*   Updated: 2023/09/18 17:17:37 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

t_ray get_shortest_distance(t_data *data, float angle)
{
	t_ray hor_ray, ver_ray, ray;
	// horizontal
	hor_ray = get_horz_intersection(data, angle);
	// vertical
	ver_ray = get_vert_intersection(data, angle);
	// shortest
	ray.distance = (hor_ray.distance < ver_ray.distance) ? hor_ray.distance : ver_ray.distance;
	ray.is_horz = (hor_ray.distance < ver_ray.distance) ? 1 : 0;
	ray.x = (hor_ray.distance < ver_ray.distance) ? hor_ray.x : ver_ray.x;
	ray.y = (hor_ray.distance < ver_ray.distance) ? hor_ray.y : ver_ray.y;
	ray.is_facing_down = (hor_ray.distance < ver_ray.distance) ? hor_ray.is_facing_down : ver_ray.is_facing_down;
	ray.is_facing_up = (hor_ray.distance < ver_ray.distance) ? hor_ray.is_facing_up : ver_ray.is_facing_up;
	ray.is_facing_left = (hor_ray.distance < ver_ray.distance) ? hor_ray.is_facing_left : ver_ray.is_facing_left;
	ray.is_facing_right = (hor_ray.distance < ver_ray.distance) ? hor_ray.is_facing_right : ver_ray.is_facing_right;
	return ray;
}
