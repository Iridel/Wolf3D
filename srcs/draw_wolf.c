/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 19:22:35 by dhill             #+#    #+#             */
/*   Updated: 2018/01/29 00:49:16 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	draw_line(t_wolf *wolf, int x)
{
	int i;

	i = 0;
	while (i < wolf->screen.win_height)
	{
		paint(&wolf->screen, x, i, wolf->buf[i]);
		++i;
	}
}

void	set_line_buf(t_wolf *wolf, int tex_x, int line_height, t_exture t)
{
	int	i;
	int	d;
	int	end;
	int	tex_y;

	i = wolf->draw_start;
	end = wolf->draw_end;
	while (i < end)
	{
		d = i * 256 - wolf->h * 128 + line_height * 128;
		tex_y = ((d * 64.0) / line_height) / 256;
		wolf->buf[i] = t.canvas[tex_x + (tex_y * t.s_line / 4)];
		++i;
	}
}

void	set_fc_buf(t_wolf *wolf, t_draw *d)
{
	double	curr_dist;
	double	weight;
	double	dist_player;
	t_coord	curr_floor;
	t_ind	floor_tex;

	dist_player = 0.0;
	d->y = wolf->draw_end + 1;
	while (d->y < wolf->h)
	{
		curr_dist = wolf->h / (2.0 * d->y - wolf->h);
		weight = (curr_dist - dist_player) / (d->dist_wall - dist_player);
		curr_floor = init_coord(weight * d->floor_wall.x + (1.0 - weight) *
		wolf->pos.x, weight * d->floor_wall.y + (1.0 - weight) * wolf->pos.y);
		floor_tex = init_pair((int)(curr_floor.x * 64) % 64,
				(int)(curr_floor.y * 64) % 64);
		wolf->buf[d->y] = wolf->textures.floor.canvas[floor_tex.x +
			(floor_tex.y * wolf->textures.floor.s_line / 4)];
		wolf->buf[wolf->h - d->y] = wolf->textures.ceiling.canvas[floor_tex.x +
			(floor_tex.y * wolf->textures.ceiling.s_line / 4)];
		++d->y;
	}
}

void	redraw(t_wolf *wolf)
{
	wolf->move_speed = FRAMETIME * 0.1;
	wolf->rot_speed = FRAMETIME * 0.075;
	move(wolf);
	init_img(&wolf->screen);
	set_screen(wolf);
	draw_img(&wolf->screen);
	if (wolf->exit)
		jump(wolf);
}
