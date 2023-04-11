/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:51:04 by chustei           #+#    #+#             */
/*   Updated: 2023/04/05 17:33:07 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

int	check_edges(void *param)
{
	t_game	*game;
	int		count;
	int		y;
	int		x;

	count = 0;
	y = -1;
	x = -1;
	game = param;
	while (++x < game->width)
		if (game->matrix[0][x] != '1' || \
			game->matrix[game->height - 1][x] != '1')
			count++;
	while (++y < game->height)
		if (game->matrix[y][0] != '1' || \
			game->matrix[y][game->width - 1] != '1')
			count++;
	if (count != 0)
	{
		ft_error("INVALID MAP: Wrong Edges\n");
		return (1);
	}
	return (count);
}

int	check_rect(void *param)
{
	t_game	*game;
	int		i;

	i = 0;
	game = param;
	while (i < game->height)
	{
		if (ft_strlen(game->matrix[i]) != (size_t)game->width)
		{
			ft_error("INVALID MAP: Wrong Shape (need rect)\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_one_exit(void *param, int y, int x)
{
	t_game	*game;
	int		i;

	i = 0;
	y = -1;
	game = param;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->matrix[y][x] == 'E')
				i++;
		}
	}
	if (i == 1)
		return (0);
	ft_error("INVALID MAP: Wrong Number of Exits\n");
	return (1);
}

int	check_one_player(void *param, int y, int x)
{
	t_game	*game;
	int		i;

	i = 0;
	y = -1;
	game = param;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->matrix[y][x] == 'P')
				i++;
		}
	}
	if (i == 1)
		return (0);
	ft_error("INVALID MAP: Wrong Number of Players\n");
	return (1);
}

int	check_collects(void *param)
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
			if (game->matrix[y][x] == 'E')
			{
				game->exit.x = x;
				game->exit.y = y;
			}
		}
	}
	if (game->num_collects <= 0)
		ft_error("INVALID MAP: Wrong Number of Coins\n");
	return (game->num_collects);
}
