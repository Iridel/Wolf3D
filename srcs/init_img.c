/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:57:57 by dhill             #+#    #+#             */
/*   Updated: 2018/01/28 22:59:23 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	init_img(t_screen *screen)
{
	screen->pic = mlx_new_image(screen->mlx, screen->win_width,
			screen->win_height);
	screen->canvas = (int *)mlx_get_data_addr(screen->pic,
			&screen->bits,
			&screen->s_line,
			&screen->endian);
}
