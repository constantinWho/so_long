/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:15:09 by chustei           #+#    #+#             */
/*   Updated: 2023/03/31 16:35:27 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

void	remove_collect(void	*param, int x, int y)
{
	int		i;
	int		coll_x;
	int		coll_y;
	t_game	*game;

	game = param;
	if (game->matrix[y / 64][x / 64] == 'C')
	{
		game->matrix[y / 64][x / 64] = '0';
		i = -1;
		while (++i < game->num_collects)
		{
			coll_x = game->collectibles[i].x;
			coll_y = game->collectibles[i].y;
			if (coll_x == x / 64 && coll_y == y / 64)
				mlx_delete_image (game->mlx, game->collectibles[i].img);
		}
	}
}

void	count_moves(mlx_key_data_t keydata, int y, int x, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS \
			&& game->matrix[(y - 64) / 64][x / 64] != '1')
		ft_printf("Move:%i\n", game->move++);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS \
			&& game->matrix[(y + 64) / 64][x / 64] != '1')
		ft_printf("Move:%i\n", game->move++);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS \
			&& game->matrix[y / 64][(x - 64) / 64] != '1')
		ft_printf("Move:%i\n", game->move++);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS \
			&& game->matrix[y / 64][(x + 64) / 64] != '1')
		ft_printf("Move:%i\n", game->move++);
}

void	key_hook(mlx_key_data_t keydata, void	*param)
{
	t_game	*game;
	int32_t	*y;
	int32_t	*x;

	game = param;
	y = &game->img.man->instances[0].y;
	x = &game->img.man->instances[0].x;
	count_moves(keydata, *y, *x, game);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS \
			&& game->matrix[(*y - 64) / 64][*x / 64] != '1')
		*y -= 64;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS \
			&& game->matrix[(*y + 64) / 64][*x / 64] != '1')
		*y += 64;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS \
			&& game->matrix[*y / 64][(*x - 64) / 64] != '1')
		*x -= 64;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS \
			&& game->matrix[*y / 64][(*x + 64) / 64] != '1')
		*x += 64;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	remove_collect(game, *x, *y);
}
