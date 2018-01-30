/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 22:23:25 by anazar            #+#    #+#             */
/*   Updated: 2018/01/28 23:00:13 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_screen		init_screen(int win_width, int win_height, char *name)
{
	t_screen	scr;

	scr.win_width = win_width;
	scr.win_height = win_height;
	scr.mlx = mlx_init();
	scr.win = mlx_new_window(scr.mlx, scr.win_width, scr.win_height, name);
	return (scr);
}
