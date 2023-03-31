/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:46:33 by chustei           #+#    #+#             */
/*   Updated: 2023/03/31 16:49:08 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

static void	place_floor(void *param, int y, int x)
{
	t_game	*game;

	y = -1;
	game = param;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
			mlx_image_to_window(game->mlx, game->img.stone, x * 64, y * 64);
	}
}

static	void	store_collects(void *param, int y, int x)
{
	t_game	*game;
	int		i;

	game = param;
	i = 0;
	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->matrix[y][x] == 'C')
			{	
				mlx_image_to_window(game->mlx, game->collectibles[i].img, \
				x * 64, y * 64);
				i++;
			}
		}
	}
}

static	void	place_objs(void *param, int y, int x)
{
	t_game	*game;

	game = param;
	y = -1;
	while (game->matrix[++y])
	{
		x = -1;
		while (game->matrix[y][++x])
		{
			if (game->matrix[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->img.finish, \
				x * 64, y * 64);
			if (game->matrix[y][x] == '1')
				mlx_image_to_window(game->mlx, game->img.box, x * 64, y * 64);
		}
	}
	mlx_image_to_window(game->mlx, game->img.man, game->p_x, game->p_y);
}

void	draw_map(void *param)
{	
	t_game			*game;
	int				y;
	int				x;

	game = param;
	y = 0;
	x = 0;
	place_floor(game, y, x);
	store_collects(game, y, x);
	place_objs(game, y, x);
}
