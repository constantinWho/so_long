/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/04/05 17:14:52 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

static void	set_game(t_game *game)
{
	game->poss_collects = 0;
	game->poss_exits = 0;
	game->move = 1;
	game->p_x = 0;
	game->p_y = 0;
	game->num_collects = 0;
	game->removed_collects = 0;
	game->texture.collect = mlx_load_png(COLLECT);
	game->texture.player = mlx_load_png(PLAYER);
	game->texture.wall = mlx_load_png(WALL);
	game->texture.exit = mlx_load_png(EXIT);
	game->texture.empty = mlx_load_png(EMPTY);
	game->img.man = mlx_texture_to_image(game->mlx, game->texture.player);
	game->img.stone = mlx_texture_to_image(game->mlx, game->texture.empty);
	game->img.box = mlx_texture_to_image(game->mlx, game->texture.wall);
	game->img.finish = mlx_texture_to_image(game->mlx, game->texture.exit);
}

void	store_player(void *param, int x, int y)
{
	t_game	*game;

	game = param;
	game->p_x = x * 64;
	game->p_y = y * 64;
}

void	store_coins(void *param, int x, int y)
{
	t_game	*game;

	game = param;
	game->collectibles[game->num_collects].img = \
	mlx_texture_to_image(game->mlx, game->texture.collect);
	game->collectibles[game->num_collects].x = x;
	game->collectibles[game->num_collects].y = y;
	game->num_collects++;
}

void	store_imgs(void *param)
{
	t_game	*game;
	int		y;
	int		x;

	game = param;
	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->matrix[y][x] == 'P')
				store_player(game, x, y);
			if (game->matrix[y][x] == 'C')
				store_coins(game, x, y);
		}
	}
}

int32_t	main(int ac, char **av)
{
	t_game			game;

	if (init_map(&game, ac, av[1]) != 0)
		return (EXIT_FAILURE);
	game.mlx = mlx_init(64 * game.width, 64 * game.height, "SO_LONG", true);
	if (!game.mlx)
		return (EXIT_FAILURE);
	set_game(&game);
	if (check_map(&game) != 0)
	{
		free_matrix(game.matrix);
		free_textures(&game.mlx);
		return (EXIT_FAILURE);
	}
	draw_map(&game.mlx);
	mlx_key_hook(game.mlx, &key_hook, &game.mlx);
	mlx_loop(game.mlx);
	if (game.matrix)
		free_matrix(game.matrix);
	free_textures(&game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
