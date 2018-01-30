/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 22:48:10 by anazar            #+#    #+#             */
/*   Updated: 2018/01/28 22:49:18 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(0);
}

int		hooks(t_wolf *wolf)
{
	redraw(wolf);
	return (0);
}

int		main(void)
{
	t_wolf wolf;

	wolf = init_wolf();
	redraw(&wolf);
	mlx_hook(wolf.screen.win, 2, 0, key_down_event, &wolf);
	mlx_hook(wolf.screen.win, 3, 0, key_up_event, &wolf);
	mlx_hook(wolf.screen.win, 4, 0, mouse_click_event, &wolf);
	mlx_hook(wolf.screen.win, 6, 0, motion_event, &wolf);
	mlx_hook(wolf.screen.win, 17, 0, close_window, &wolf);
	mlx_loop_hook(wolf.screen.mlx, hooks, &wolf);
	mlx_loop(wolf.screen.mlx);
}
