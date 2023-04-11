/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:51:04 by chustei           #+#    #+#             */
/*   Updated: 2023/04/05 17:34:12 by chustei          ###   ########.fr       */
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
			if (game->matrix[y][x] != '0' && game->matrix[y][x] != '1' && \
				game->matrix[y][x] != 'E' && game->matrix[y][x] != 'P' && \
				game->matrix[y][x] != 'C')
			{
				ft_error("INVALID MAP: Wrong Chars\n");
				return (1);
			}
		}
	}
	return (0);
}

void	print_messages(void *param, int num_err)
{
	t_game	*game;

	game = param;
	ft_printf("Foud Paths:\n------\n");
	ft_printf("COINS [%i/%i]\n", game->poss_collects, game->num_collects);
	ft_printf("EXIT [%i]\n------\n", game->poss_exits);
	ft_printf("MAP ERRORS: %i\n", num_err);
	ft_printf("============\n");
}

int	check_map(void	*param)
{
	t_game	*game;
	int		num_err;

	num_err = 0;
	game = param;
	store_imgs(game);
	num_err += check_chars(game);
	num_err += check_edges(game);
	num_err += check_rect(game);
	num_err += check_one_exit(game, game->height, game->width);
	num_err += check_one_player(game, game->height, game->width);
	if (check_collects(game) < 1)
		num_err += 1;
	num_err += check_if_solvable(game);
	print_messages(game, num_err);
	return (num_err);
}
