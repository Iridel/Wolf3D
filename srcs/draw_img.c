/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:59:34 by dhill             #+#    #+#             */
/*   Updated: 2018/01/28 19:22:01 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	draw_img(t_screen *screen)
{
	mlx_put_image_to_window(screen->mlx, screen->win, screen->pic, 0, 0);
	mlx_destroy_image(screen->mlx, screen->pic);
}
