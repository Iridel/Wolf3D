/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 00:04:56 by anazar            #+#    #+#             */
/*   Updated: 2018/01/29 00:49:28 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	draw_wall(t_draw *d, t_wolf *wolf)
{
	d->ray = init_ray(wolf, d->x, wolf->w);
	d->perp_wall_dist = raycast(&d->ray, wolf);
	d->line_height = (int)(wolf->h / d->perp_wall_dist);
	wolf->draw_start = -d->line_height / 2 + wolf->h / 2;
	wolf->draw_start < 0 ? wolf->draw_start = 0 : 0;
	wolf->draw_end = d->line_height / 2 + wolf->h / 2;
	wolf->draw_end >= wolf->h ? wolf->draw_end = wolf->h - 1 : 0;
	d->wall_x = (d->ray.side % 2) ? wolf->pos.x + d->perp_wall_dist *
		d->ray.dir.x : wolf->pos.y + d->perp_wall_dist * d->ray.dir.y;
	d->wall_x -= floor(d->wall_x);
	d->tex_x = (int)(d->wall_x * 64.0);
	(d->ray.side % 2) && d->ray.dir.x > 0 ? d->tex_x = 64.0 - d->tex_x - 1 : 0;
	!(d->ray.side % 2) && d->ray.dir.y < 0 ? d->tex_x = 64.0 - d->tex_x - 1 : 0;
	if (d->ray.side == 0)
		d->texture = wolf->textures.n_wall;
	else if (d->ray.side == 1)
		d->texture = wolf->textures.e_wall;
	else if (d->ray.side == 2)
		d->texture = wolf->textures.s_wall;
	else if (d->ray.side == 3)
		d->texture = wolf->textures.w_wall;
	else
		d->texture = wolf->textures.blank;
	set_line_buf(wolf, d->tex_x, d->line_height, d->texture);
}

void	draw_ceiling(t_draw *d, t_wolf *wolf)
{
	if (d->ray.side == 0 || (d->ray.side == 4 && d->ray.dir.x < 0))
		d->floor_wall = init_coord(d->ray.map.x, d->ray.map.y + d->wall_x);
	else if (d->ray.side == 1 || (d->ray.side == 5 && d->ray.dir.y > 0))
		d->floor_wall = init_coord(d->ray.map.x + d->wall_x, d->ray.map.y);
	else if (d->ray.side == 2 || (d->ray.side == 4 && d->ray.dir.x > 0))
		d->floor_wall = init_coord(d->ray.map.x + 1.0,
				d->ray.map.y + d->wall_x);
	else
		d->floor_wall = init_coord(d->ray.map.x + d->wall_x,
				d->ray.map.y + 1.0);
	d->dist_wall = d->perp_wall_dist;
	wolf->draw_end < 0 ? wolf->draw_end = wolf->h : 0;
	set_fc_buf(wolf, d);
}

void	set_screen(t_wolf *wolf)
{
	t_draw	d;

	d.x = 0;
	while (d.x < wolf->w)
	{
		draw_wall(&d, wolf);
		draw_ceiling(&d, wolf);
		draw_line(wolf, d.x);
		++d.x;
	}
}
