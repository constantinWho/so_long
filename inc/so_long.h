/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:54:22 by chustei           #+#    #+#             */
/*   Updated: 2023/03/26 19:23:07 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_collectible {
	int	x;
	int	y;
	int	is_visible;
}	t_collectible;

typedef struct s_textures
{
	mlx_texture_t	*player;
	mlx_texture_t	*collect;
	mlx_texture_t	*empty;
	mlx_texture_t	*wall;
	mlx_texture_t	*exit;
}	t_textures;

typedef struct s_imgs
{
	mlx_image_t		*man;
	mlx_image_t		*coin;
	mlx_image_t		*stone;
	mlx_image_t		*box;
	mlx_image_t		*finish;
}	t_imgs;

typedef struct s_game
{
	mlx_t			*mlx;
	t_textures		texture;
	t_imgs			img;
	int				move;
	int				width;
	int				height;
	char			**matrix;
	char			*buff;
	char			*line;
}	t_game;

#endif
