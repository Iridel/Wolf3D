/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 22:23:49 by anazar            #+#    #+#             */
/*   Updated: 2018/01/28 23:46:54 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_ray	init_ray(t_wolf *wolf, int x, int w)
{
	t_ray	ray;

	ray.x = x;
	ray.camera_x = 2 * ray.x / (double)w - 1;
	ray.dir = init_coord(wolf->dir.x + wolf->plane.x * ray.camera_x,
			wolf->dir.y + wolf->plane.y * ray.camera_x);
	ray.map = init_pair((int)wolf->pos.x, (int)wolf->pos.y);
	ray.delta_dist = init_coord(ABS(1 / ray.dir.x), ABS(1 / ray.dir.y));
	ray.step = init_pair(0, 0);
	ray.hit = 0;
	ray.side = 0;
	return (ray);
}

void	set_x(t_ray *ray, t_wolf *wolf)
{
	ray->side_dist.x += ray->delta_dist.x;
	ray->map.x += ray->step.x;
	ray->side = ray->step.x > 0 ? 0 : 2;
	if (ft_isupper(wolf->map[ray->map.x][ray->map.y]) ||
			wolf->map[ray->map.x][ray->map.y] == '5')
		ray->side = 4;
}

void	set_y(t_ray *ray, t_wolf *wolf)
{
	ray->side_dist.y += ray->delta_dist.y;
	ray->map.y += ray->step.y;
	ray->side = ray->step.y > 0 ? 1 : 3;
	if (ft_isupper(wolf->map[ray->map.x][ray->map.y]) ||
			wolf->map[ray->map.x][ray->map.y] == '5')
		ray->side = 5;
}

double	dda(t_ray *ray, t_wolf *wolf)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
			set_x(ray, wolf);
		else
			set_y(ray, wolf);
		if (wolf->map[ray->map.x][ray->map.y] == '1' ||
				ft_isupper(wolf->map[ray->map.x][ray->map.y]) ||
				wolf->map[ray->map.x][ray->map.y] == '5')
			ray->hit = 1;
	}
	if (ray->side == 0 || ray->side == 2 || ray->side == 4)
		return ((ray->map.x - wolf->pos.x +
					(1 - ray->step.x) / 2) / ray->dir.x);
	else
		return ((ray->map.y - wolf->pos.y +
					(1 - ray->step.y) / 2) / ray->dir.y);
}

double	raycast(t_ray *ray, t_wolf *wolf)
{
	ray->step.x = ray->dir.x < 0 ? -1 : 1;
	ray->step.y = ray->dir.y < 0 ? -1 : 1;
	ray->side_dist.x = (ray->dir.x < 0 ? (wolf->pos.x - ray->map.x) :
			(ray->map.x + 1.0 - wolf->pos.x)) * ray->delta_dist.x;
	ray->side_dist.y = (ray->dir.y < 0 ? (wolf->pos.y - ray->map.y) :
			(ray->map.y + 1.0 - wolf->pos.y)) * ray->delta_dist.y;
	return (dda(ray, wolf));
}
