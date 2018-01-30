/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 22:22:57 by anazar            #+#    #+#             */
/*   Updated: 2018/01/28 23:17:48 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		mouse_click_event(int button, int x, int y, t_wolf *wolf)
{
	t_ray	r;
	double	d;

	r = init_ray(wolf, x, wolf->w);
	if (button == 1)
	{
		wolf->lclicked = 1;
		d = raycast(&r, wolf);
		if (r.side == 4 || r.side == 5)
		{
			wolf->exit = 1;
			wolf->clicked_on = wolf->map[r.map.x][r.map.y];
			redraw(wolf);
			return (0);
		}
	}
	(void)y;
	return (0);
}

int		key_up_event(int keycode, t_wolf *wolf)
{
	if (keycode == 126 || keycode == 13)
		wolf->flags.f = 0;
	if (keycode == 125 || keycode == 1)
		wolf->flags.b = 0;
	if (keycode == 124 || keycode == 2)
		wolf->flags.r = 0;
	if (keycode == 123 || keycode == 0)
		wolf->flags.l = 0;
	wolf->draw = 1;
	redraw(wolf);
	return (0);
}

int		close_window(t_wolf *wolf)
{
	mlx_destroy_window(wolf->screen.mlx, wolf->screen.win);
	exit(0);
	return (0);
}

int		motion_event(int x, int y, t_wolf *wolf)
{
	(void)y;
	wolf->last_mp = x;
	return (0);
}

int		key_down_event(int keycode, t_wolf *wolf)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 126 || keycode == 13)
		wolf->flags.f = 1;
	if (keycode == 125 || keycode == 1)
		wolf->flags.b = 1;
	if (keycode == 124 || keycode == 2)
		wolf->flags.r = 1;
	if (keycode == 123 || keycode == 0)
		wolf->flags.l = 1;
	wolf->draw = 1;
	redraw(wolf);
	return (1);
}
