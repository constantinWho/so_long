/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/03/31 17:51:36 by chustei          ###   ########.fr       */
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

void	store_player_and_collectibles(void *param, int x, int y)
{
	t_game	*game;

	game = param;
	if (game->matrix[y][x] == 'P')
	{
		game->p_x = x * 64;
		game->p_y = y * 64;
	}
	if (game->matrix[y][x] == 'C')
	{
		game->collectibles[game->num_collects].img = \
		mlx_texture_to_image(game->mlx, game->texture.collect);
		game->collectibles[game->num_collects].x = x;
		game->collectibles[game->num_collects].y = y;
		game->num_collects++;
	}
}

int32_t	main(int ac, char **av)
{
	t_game			game;

	init_map(&game, ac, av[1]);
	game.mlx = mlx_init(64 * game.width, 64 * game.height, "SO_LONG", true);
	set_game(&game);
	if (!game.mlx || check_map(&game) != 0)
		return (EXIT_FAILURE);
	draw_map(&game.mlx);
	mlx_key_hook(game.mlx, &key_hook, &game.mlx);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free(game.matrix);
	return (EXIT_SUCCESS);
}
