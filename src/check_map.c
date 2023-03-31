/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:51:04 by chustei           #+#    #+#             */
/*   Updated: 2023/03/31 17:45:28 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

static	int	check_chars(void *param)
{
	t_game	*game;
	int		x;
	int		y;

	game = param;
	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			store_player_and_collectibles(game, x, y);
			if (game->matrix[y][x] != '0' && game->matrix[y][x] != '1' && \
				game->matrix[y][x] != 'E' && game->matrix[y][x] != 'P' && \
				game->matrix[y][x] != 'C')
			{
				ft_printf("INVALID MAP: Wrong Chars\n");
				return (1);
			}
		}
	}
	game = param;
	return (0);
}

static	int	find_collects(void *param, int x, int y, int i)
{
	t_game	*game;

	game = param;
	game->dup_matrix[y][x] = 'x';
	if (game->collectibles[i].x == x && game->collectibles[i].y == y)
	{
		game->poss_collects++;
		return (0);
	}
	if (game->dup_matrix[y][x + 1] != '1' && game->dup_matrix[y][x + 1] != 'x')
		find_collects(game, x + 1, y, i);
	if (game->dup_matrix[y][x - 1] != '1' && game->dup_matrix[y][x - 1] != 'x')
		find_collects(game, x - 1, y, i);
	if (game->dup_matrix[y + 1][x] != '1' && game->dup_matrix[y + 1][x] != 'x')
		find_collects(game, x, y + 1, i);
	if (game->dup_matrix[y - 1][x] != '1' && game->dup_matrix[y - 1][x] != 'x')
		find_collects(game, x, y - 1, i);
	return (1);
}

static	void	find_exit(void *param, int x, int y)
{
	t_game	*game;

	game = param;
	game->dup_matrix[y][x] = 'x';
	if (game->exit.x == x && game->exit.y == y)
		game->poss_exits++;
	if (game->dup_matrix[y][x + 1] != '1' && game->dup_matrix[y][x + 1] != 'x')
		find_exit(game, x + 1, y);
	if (game->dup_matrix[y][x - 1] != '1' && game->dup_matrix[y][x - 1] != 'x')
		find_exit(game, x - 1, y);
	if (game->dup_matrix[y + 1][x] != '1' && game->dup_matrix[y + 1][x] != 'x')
		find_exit(game, x, y + 1);
	if (game->dup_matrix[y - 1][x] != '1' && game->dup_matrix[y - 1][x] != 'x')
		find_exit(game, x, y - 1);
}

static	int	check_if_solvable(void *param)
{
	t_game	*game;
	int		x;
	int		y;
	int		i;

	game = param;
	x = game->p_x / 64;
	y = game->p_y / 64;
	i = 0;
	while (i < game->num_collects)
	{
		game->dup_matrix = ft_split(game->line, '\n');
		find_collects(game, x, y, i);
		free(game->dup_matrix);
		i++;
	}
	game->dup_matrix = ft_split(game->line, '\n');
	find_exit(game, x, y);
	free(game->dup_matrix);
	ft_printf("COINS [%i/%i] & EXIT [%i] Paths Found;\n", \
		game->poss_collects, game->num_collects, game->poss_exits);
	if (game->poss_collects == game->num_collects && game->poss_exits == 1)
		return (0);
	return (1);
}

int	check_map(void	*param)
{
	t_game	*game;
	int		num_err;

	num_err = 0;
	game = param;
	num_err += check_chars(game);
	num_err += check_edges(game);
	num_err += check_rect(game);
	num_err += check_one_exit(game, game->height, game->width);
	num_err += check_one_player(game, game->height, game->width);
	if (check_collects(game) > 0)
		num_err += 0;
	num_err += check_if_solvable(game);
	ft_printf("MAP ERRORS: %i\n", num_err);

	return (num_err);
}
