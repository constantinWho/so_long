/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_solvable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:20:15 by chustei           #+#    #+#             */
/*   Updated: 2023/04/05 17:34:23 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

static	void	replace_edges(void *param)
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
			if (y == 0 || x == 0 || y == game->height - 1 \
				|| x == game->width - 1)
				game->dup_matrix[y][x] = '1';
		}
	}
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

static	void	check_exit(void *param, int x, int y)
{
	t_game	*game;
	int		i;

	i = -1;
	game = param;
	game->dup_matrix = ft_split(game->line, '\n');
	replace_edges(game);
	find_exit(game, x, y);
	while (game->dup_matrix[++i])
		free(game->dup_matrix[i]);
	free(game->dup_matrix);
}

int	check_if_solvable(void *param)
{
	t_game	*game;
	int		i;
	int		j;

	j = -1;
	game = param;
	if (game->p_x == 0 && game->p_y == 0)
	{
		free(game->line);
		return (1);
	}
	i = -1;
	while (++i < game->num_collects)
	{
		game->dup_matrix = ft_split(game->line, '\n');
		replace_edges(game);
		find_collects(game, game->p_x / 64, game->p_y / 64, i);
		free_matrix(game->dup_matrix);
	}
	check_exit(game, game->p_x / 64, game->p_y / 64);
	free(game->line);
	if (game->poss_collects == game->num_collects && game->poss_exits == 1)
		return (0);
	return (1);
}
