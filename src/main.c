/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/03/26 19:32:54 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

#define PLAYER "./textures/PLAYER.png"
#define COLLECT "./textures/COIN.png"
#define EMPTY "./textures/GROUND.png"
#define WALL "./textures/BOX.png"
#define EXIT "./textures/EXIT.png"

void draw_map(void *param)
{	
	t_game			*game;
	int				y;
	int				x;
	int				i;
	int				num_collects;

	num_collects = 0;
	game = param;
	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			mlx_image_to_window(game->mlx, game->img.stone, x * 64, y * 64);
			if (game->matrix[y][x] == 'C')
				num_collects++;
		}
	}
	t_collectible	collectibles[num_collects];
	y = -1;
	i = 0;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->matrix[y][x] == 'C')
			{
				collectibles[i].x = x;
				collectibles[i].y = y;
				collectibles[i].is_visible = 1;
				i++;
			}
		}
	}
	y = -1;
	while (game->matrix[++y])
	{
		x = -1;
		while (game->matrix[y][++x])
		{
			if (game->matrix[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->img.coin, x * 64, y * 64);
			if (game->matrix[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->img.finish, x * 64, y * 64);
			if (game->matrix[y][x] == 'P')
				mlx_image_to_window(game->mlx, game->img.man, x * 64, y * 64);
			if (game->matrix[y][x] == '1')
				mlx_image_to_window(game->mlx, game->img.box, x * 64, y * 64);
		}
	}
}

void	key_hook(mlx_key_data_t keydata, void	*param)
{
	t_game	*game;
	int32_t	*y;
	int32_t	*x;

	game = param;
	y = &game->img.man->instances[0].y;
	x = &game->img.man->instances[0].x;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS \
			&& game->matrix[(*y - 64) / 64][*x / 64] != '1')
	{
		*y -= 64;
		if (game->matrix[*y / 64][*x / 64] == 'C')
		{
			game->matrix[*y / 64][*x / 64] = 'P';
/* 			mlx_image_to_window(game->mlx, game->img.stone, *x, *y); */
			mlx_delete_image(game->mlx, game->img.coin);
/* 			mlx_image_to_window(game->mlx, game->img.man, *x, *y); */
			ft_printf("Move:%i\n", game->move++);
		}
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS \
			&& game->matrix[(*y + 64) / 64][*x / 64] != '1')
	{
		*y += 64;
		ft_printf("Move:%i\n", game->move++);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS \
			&& game->matrix[*y / 64][(*x - 64) / 64] != '1')
	{
		*x -= 64;
		ft_printf("Move:%i\n", game->move++);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS \
			&& game->matrix[*y / 64][(*x + 64) / 64] != '1')
	{
		*x += 64;
		ft_printf("Move:%i\n", game->move++);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(game->mlx);
		ft_printf("Move:%i\n", game->move++);
	}
}

void	set_game(t_game *game)
{
	game->move = 1;
}

void	load_textures(t_textures *texture)
{
	texture->collect = mlx_load_png(COLLECT);
	texture->player = mlx_load_png(PLAYER);
	texture->wall = mlx_load_png(WALL);
	texture->exit = mlx_load_png(EXIT);
	texture->empty = mlx_load_png(EMPTY);
}

int32_t	main(void)
{
	t_game			game;
	int				fd;

	fd = open ("./maps/map.ber", O_RDONLY);
	game.buff = get_next_line(fd);
	game.line = "";
	game.width = ft_strlen(game.buff) - 1;
	game.height = 0;
	while (game.buff)
	{
		game.line = ft_strjoin (game.line, game.buff);
		game.buff = get_next_line(fd);
		game.height++;
	}
	game.matrix = ft_split(game.line, '\n');
	free(game.line);
	free(game.buff);
	close(fd);
	int e = -1;
	while (game.matrix[++e])
		printf("matrix row%i: %s\n", e, game.matrix[e]);
	game.mlx = mlx_init(64 * game.width, 64 * game.height, "SO_LONG", true);
	if (!game.mlx)
		return (EXIT_FAILURE);
	set_game(&game);
	load_textures(&game.texture);
	game.img.man = mlx_texture_to_image(game.mlx, game.texture.player);
	game.img.coin = mlx_texture_to_image(game.mlx, game.texture.collect);
	game.img.stone = mlx_texture_to_image(game.mlx, game.texture.empty);
	game.img.box = mlx_texture_to_image(game.mlx, game.texture.wall);
	game.img.finish = mlx_texture_to_image(game.mlx, game.texture.exit);
	draw_map(&game.mlx);
	mlx_key_hook(game.mlx, &key_hook, &game.mlx);
	mlx_loop(game.mlx);
	mlx_delete_image(game.mlx, game.img.man);
	mlx_delete_texture(game.texture.player);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
