/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:32:46 by chustei           #+#    #+#             */
/*   Updated: 2023/03/31 17:51:39 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

static void	get_matrix(void *param, int fd)
{
	t_game	*game;

	game = param;
	game->buff = get_next_line(fd);
	game->line = "";
	game->width = ft_strlen(game->buff) - 1;
	game->height = 0;
	while (game->buff)
	{
		game->line = ft_strjoin (game->line, game->buff);
		game->buff = get_next_line(fd);
		game->height++;
	}
	game->matrix = ft_split(game->line, '\n');
}

int	init_map(void *param, int ac, char *av)
{
	t_game	*game;
	int		fd;

	game = param;
	if (ac == 2)
	{
		fd = open (av, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("WRONG FILE EXTENSION: Use \".ber\"\n");
			return (EXIT_FAILURE);
		}
		get_matrix(game, fd);
		free(game->buff);
		close(fd);
	}
	return (EXIT_SUCCESS);
}
