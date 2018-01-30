/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 22:23:39 by anazar            #+#    #+#             */
/*   Updated: 2018/01/28 23:39:13 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	rotate(t_wolf *wolf)
{
	double old_dir_x;
	double old_strafe_x;
	double old_plane_x;
	double corr;

	old_dir_x = wolf->dir.x;
	old_strafe_x = wolf->strafe.x;
	old_plane_x = wolf->plane.x;
	corr = wolf->last_mp < wolf->mid ? R_CHANGE(wolf->last_mp, 0, 0.1,
	wolf->lturn, 0) : R_CHANGE(wolf->last_mp, -0.1, 0, wolf->w, wolf->rturn);
	if ((wolf->last_mp > 0 && wolf->last_mp < wolf->lturn) ||
			(wolf->last_mp > wolf->rturn && wolf->last_mp < wolf->w))
	{
		wolf->dir = init_coord(wolf->dir.x * cos(corr) -
				wolf->dir.y * sin(corr),
				old_dir_x * sin(corr) + wolf->dir.y * cos(corr));
		wolf->plane = init_coord(wolf->plane.x * cos(corr) -
				wolf->plane.y * sin(corr),
				old_plane_x * sin(corr) + wolf->plane.y * cos(corr));
		wolf->strafe = init_coord(wolf->strafe.x * cos(corr) -
				wolf->strafe.y * sin(corr),
				old_strafe_x * sin(corr) + wolf->strafe.y * cos(corr));
	}
}

void	strafe(t_wolf *wolf)
{
	if (wolf->flags.r)
	{
		if (wolf->map[(int)(wolf->pos.x - wolf->strafe.x *
					wolf->move_speed)][(int)wolf->pos.y] != '1')
			wolf->pos.x -= wolf->strafe.x * wolf->move_speed;
		if (wolf->map[(int)wolf->pos.x][(int)(wolf->pos.y -
					wolf->strafe.y * wolf->move_speed)] != '1')
			wolf->pos.y -= wolf->strafe.y * wolf->move_speed;
	}
	if (wolf->flags.l)
	{
		if (wolf->map[(int)(wolf->pos.x + wolf->strafe.x *
					wolf->move_speed)][(int)wolf->pos.y] != '1')
			wolf->pos.x += wolf->strafe.x * wolf->move_speed;
		if (wolf->map[(int)wolf->pos.x][(int)(wolf->pos.y +
					wolf->strafe.y * wolf->move_speed)] != '1')
			wolf->pos.y += wolf->strafe.y * wolf->move_speed;
	}
}

void	move(t_wolf *wolf)
{
	if (wolf->flags.f)
	{
		if (wolf->map[(int)(wolf->pos.x + wolf->dir.x *
					wolf->move_speed)][(int)wolf->pos.y] != '1')
			wolf->pos.x += wolf->dir.x * wolf->move_speed;
		if (wolf->map[(int)wolf->pos.x][(int)(wolf->pos.y +
					wolf->dir.y * wolf->move_speed)] != '1')
			wolf->pos.y += wolf->dir.y * wolf->move_speed;
	}
	if (wolf->flags.b)
	{
		if (wolf->map[(int)(wolf->pos.x - wolf->dir.x *
					wolf->move_speed)][(int)wolf->pos.y] != '1')
			wolf->pos.x -= wolf->dir.x * wolf->move_speed;
		if (wolf->map[(int)wolf->pos.x][(int)(wolf->pos.y -
					wolf->dir.y * wolf->move_speed)] != '1')
			wolf->pos.y -= wolf->dir.y * wolf->move_speed;
	}
	strafe(wolf);
	rotate(wolf);
	wolf->draw = 1;
}
