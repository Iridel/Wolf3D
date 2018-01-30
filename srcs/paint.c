/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:58:36 by dhill             #+#    #+#             */
/*   Updated: 2018/01/28 23:35:39 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	paint(t_screen *screen, int x, int y, t_color color)
{
	int	pos;

	pos = x + (y * screen->s_line / 4);
	if (pos >= 0 && pos < screen->win_height * screen->win_width)
		if ((x >= 0 && x < screen->win_width) &&
				(y >= 0 && y < screen->win_height))
			screen->canvas[pos] = color;
}
