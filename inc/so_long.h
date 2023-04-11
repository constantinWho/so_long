/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:54:22 by chustei           #+#    #+#             */
/*   Updated: 2023/04/05 17:30:26 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <memory.h>
# define PLAYER "./textures/PLAYER.png"
# define COLLECT "./textures/COIN.png"
# define EMPTY "./textures/GROUND.png"
# define WALL "./textures/BOX.png"
# define EXIT "./textures/EXIT.png"

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
	mlx_image_t		*stone;
	mlx_image_t		*box;
	mlx_image_t		*finish;
}	t_imgs;

typedef struct s_collectible {
	mlx_image_t		*img;
	int				x;
	int				y;
}	t_collectible;

typedef struct s_exit {
	int				x;
	int				y;
}	t_exit;

typedef struct s_game
{
	mlx_t			*mlx;
	t_textures		texture;
	t_imgs			img;
	int				num_collects;
	int				removed_collects;
	t_collectible	collectibles[1000];
	t_exit			exit;
	int				move;
	int				width;
	int				height;
	int				p_x;
	int				p_y;
	int				e_x;
	int				e_y;
	int				poss_collects;
	int				poss_exits;
	char			**matrix;
	char			**dup_matrix;
	char			*buff;
	char			*line;
}	t_game;

int		init_map(void *param, int ac, char *av);
void	draw_map(void *param);
int		check_map(void	*param);
int		check_edges(void *param);
int		check_rect(void *param);
int		check_one_player(void *param, int y, int x);
int		check_one_exit(void *param, int y, int x);
int		check_collects(void *param);
void	remove_collect(void	*param, int x, int y);
void	count_moves(mlx_key_data_t keydata, int y, int x, void *param);
void	key_hook(mlx_key_data_t keydata, void	*param);
void	store_imgs(void *param);
int		check_if_solvable(void *param);
void	free_matrix(char **matrix);
void	free_textures(void *param);
void	ft_error(char *str);

#endif