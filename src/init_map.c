/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:32:46 by chustei           #+#    #+#             */
/*   Updated: 2023/04/05 17:32:34 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

static	int	create_2d(void *param, int fd)
{
	t_game	*game;

	game = param;
	while (game->buff)
	{
		if (ft_strlen(game->buff) - 1 == 0)
		{
			ft_error("YOU HAVE AT LEAST ONE EMPTY LINE\n");
			free(game->buff);
			return (1);
		}
		game->line = ft_strjoin (game->line, game->buff);
		free(game->buff);
		game->buff = get_next_line(fd);
		game->height++;
	}
	return (0);
}

static int	get_matrix(void *param, int fd)
{
	t_game	*game;

	game = param;
	game->buff = get_next_line(fd);
	if (!game->buff)
	{
		free(game->buff);
		return (EXIT_FAILURE);
	}
	game->line = ft_strdup("");
	game->width = ft_strlen(game->buff) - 1;
	game->height = 0;
	if (create_2d(game, fd) == 1)
		return (EXIT_FAILURE);
	game->matrix = ft_split(game->line, '\n');
	free(game->buff);
	return (EXIT_SUCCESS);
}

static	int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[len - 1] == 'r' && file[len - 2] == 'e' \
		&& file[len - 3] == 'b' && file[len - 4] == '.')
		return (0);
	ft_error("WRONG FILE EXTENSION: Use \".ber\"\n");
	return (1);
}

static	int	check_fd(void *param, int fd)
{
	t_game	*game;

	game = param;
	if (fd == -1)
	{
		ft_error("FILE DOES NOT EXIST\n");
		return (1);
	}
	return (0);
}

int	init_map(void *param, int ac, char *av)
{
	t_game	*game;
	int		fd;

	game = param;
	if (ac == 2 && check_extension(av) == 0)
	{
		fd = open (av, O_RDONLY);
		if (check_fd(game, fd) == 1)
			return (EXIT_FAILURE);
		if (get_matrix(game, fd) == 1)
		{
			free(game->line);
			if (!game->matrix)
				free_matrix(game->matrix);
			close(fd);
			return (EXIT_FAILURE);
		}
		close(fd);
	}
	else
	{
		ft_error("A FILE PATH NEEDED\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
