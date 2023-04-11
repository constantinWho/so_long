/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:25:17 by chustei           #+#    #+#             */
/*   Updated: 2023/04/05 17:29:50 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/inc/libft.h"
#include "../inc/so_long.h"

void	free_matrix(char **matrix)
{
	int		j;

	if (!matrix || !*matrix)
		return ;
	j = -1;
	while (matrix[++j])
	{
		if (matrix[j])
		{
			free(matrix[j]);
			matrix[j] = NULL;
		}
	}
	free(matrix);
}

void	free_textures(void *param)
{
	t_game	*game;

	game = param;
	mlx_delete_texture(game->texture.player);
	mlx_delete_texture(game->texture.empty);
	mlx_delete_texture(game->texture.wall);
	mlx_delete_texture(game->texture.exit);
	mlx_delete_texture(game->texture.collect);
}

void	ft_error(char *str)
{
	ft_printf("Error\n");
	ft_printf("%s", str);
}
