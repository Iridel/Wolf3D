/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 22:23:29 by anazar            #+#    #+#             */
/*   Updated: 2018/01/29 00:54:49 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	win_screen(t_wolf *wolf)
{
	mlx_string_put(wolf->screen.mlx, wolf->screen.win,
		wolf->screen.win_width / 2, wolf->screen.win_height / 2,
		ft_rgb(0x32, 0xcd, 0x32), "You found the exit!");
}

void	load_room(t_wolf *wolf)
{
	wolf->map = wolf->world[wolf->it].room;
	ft_putstr("You are now at room : ");
	ft_putendl(wolf->world[wolf->it].name);
	wolf->pos = pos_of(wolf->map, wolf->clicked_on);
	ft_putstr("X : ");
	ft_putnbr((int)wolf->pos.x);
	ft_putstr(", Y : ");
	ft_putnbr((int)wolf->pos.y);
	ft_putchar('\n');
	wolf->clicked_on = '2';
	wolf->exit = 0;
}

void	jump(t_wolf *wolf)
{
	if (wolf->clicked_on == 'A')
		wolf->it = wolf->it == 0 ? 1 : 0;
	else if (wolf->clicked_on == 'B')
		wolf->it = wolf->it == 0 ? 2 : 0;
	else if (wolf->clicked_on == 'C')
		wolf->it = wolf->it == 0 ? 5 : 0;
	else if (wolf->clicked_on == 'D')
		wolf->it = wolf->it == 1 ? 5 : 1;
	else if (wolf->clicked_on == 'E')
		wolf->it = wolf->it == 1 ? 2 : 1;
	else if (wolf->clicked_on == 'F')
		wolf->it = wolf->it == 2 ? 3 : 2;
	else if (wolf->clicked_on == 'G')
		wolf->it = wolf->it == 3 ? 4 : 3;
	else if (wolf->clicked_on == 'H')
		wolf->it = wolf->it == 4 ? 2 : 4;
	if (wolf->clicked_on != '5')
		load_room(wolf);
	else
		win_screen(wolf);
}
