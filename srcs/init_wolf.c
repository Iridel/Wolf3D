/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 22:23:19 by anazar            #+#    #+#             */
/*   Updated: 2018/01/28 23:33:47 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_exture	init_texture(char *filename, void *mlx)
{
	t_exture	t;

	t.pic = mlx_xpm_file_to_image(mlx, filename, &t.x, &t.y);
	t.canvas = (int*)mlx_get_data_addr(t.pic, &t.bits, &t.s_line, &t.endian);
	return (t);
}

t_extures	init_textures(void *mlx)
{
	t_extures	t;

	t.n_wall = init_texture("./includes/NbrickWall.xpm", mlx);
	t.s_wall = init_texture("./includes/SbrickWall.xpm", mlx);
	t.e_wall = init_texture("./includes/EbrickWall.xpm", mlx);
	t.w_wall = init_texture("./includes/WbrickWall.xpm", mlx);
	t.floor = init_texture("./includes/Floor.xpm", mlx);
	t.blank = init_texture("./includes/Blank.xpm", mlx);
	t.ceiling = init_texture("./includes/Ceiling.xpm", mlx);
	return (t);
}

void		init_rooms(t_wolf *wolf)
{
	wolf->world[0].room = parse("./maps/start.map");
	wolf->world[0].name = "start.map";
	wolf->world[1].room = parse("./maps/side.map");
	wolf->world[1].name = "side.map";
	wolf->world[2].room = parse("./maps/large.map");
	wolf->world[2].name = "large.map";
	wolf->world[3].room = parse("./maps/largest.map");
	wolf->world[3].name = "largest.map";
	wolf->world[4].room = parse("./maps/other.map");
	wolf->world[4].name = "other.map";
	wolf->world[5].room = parse("./maps/loop.map");
	wolf->world[5].name = "loop.map";
}

t_coord		pos_of(char **arr, int val)
{
	int		x;
	int		y;

	x = 0;
	while (arr[x])
	{
		y = 0;
		while (arr[x][y])
		{
			if (arr[x][y] == val)
			{
				return (init_coord(x + 0.5, y + 0.5));
			}
			++y;
		}
		++x;
	}
	return (init_coord(1, 1));
}

t_wolf		init_wolf(void)
{
	t_wolf	wolf;

	init_rooms(&wolf);
	wolf.it = 0;
	wolf.map = wolf.world[wolf.it].room;
	wolf.pos = pos_of(wolf.map, '2');
	wolf.dir = init_coord(-1, 0);
	wolf.strafe = init_coord(0, -1);
	wolf.plane = init_coord(0, 0.66);
	wolf.w = 512 * 2;
	wolf.h = 3 * wolf.w / 4;
	wolf.exit = 0;
	wolf.lturn = wolf.w / 3;
	wolf.rturn = 2 * wolf.w / 3;
	wolf.mid = wolf.w / 2;
	wolf.last_mp = wolf.mid;
	wolf.screen = init_screen(wolf.w, wolf.h, "Wolf3d");
	wolf.textures = init_textures(wolf.screen.mlx);
	wolf.buf = (unsigned *)ft_memalloc(sizeof(t_color) *
			wolf.screen.win_height);
	wolf.clicked_on = '2';
	return (wolf);
}
