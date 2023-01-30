/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:14:20 by loris             #+#    #+#             */
/*   Updated: 2022/11/02 09:00:46 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	g_nb_move;

int	close_win(t_base *base)
{
	mlx_destroy_image(base->mlx, base->img.wall);
	mlx_destroy_image(base->mlx, base->img.empty);
	mlx_destroy_image(base->mlx, base->img.exit);
	mlx_destroy_image(base->mlx, base->img.player);
	mlx_destroy_image(base->mlx, base->img.collectible);
	free(base->map);
	mlx_destroy_window(base->mlx, base->win);
	mlx_destroy_display(base->mlx);
	free(base);
	exit (0);
}

int	close_victory(t_base *base)
{
	ft_printf("Number of movements: %i\n", g_nb_move + 1);
	close_win(base);
	exit (0);
}

int	dispatch(int keycode, t_base *base)
{
	if (keycode == KEY_ESC)
		close_win(base);
	if (keycode == KEY_W || keycode == KEY_D || \
	keycode == KEY_S || keycode == KEY_A)
	{
		if (move(keycode, base) == 1)
		{
			g_nb_move++;
			display_game(base, 0, 0, 0);
			ft_printf("Number of movements: %i\n", g_nb_move);
		}
	}
	return (0);
}

void	set_assets(t_base *base)
{
	base->img.wall = mlx_xpm_file_to_image(base->mlx, \
	"./assets/wall.xpm", &base->img.img_width, &base->img.img_height);
	base->img.empty = mlx_xpm_file_to_image(base->mlx, \
	"./assets/empty.xpm", &base->img.img_width, &base->img.img_height);
	base->img.exit = mlx_xpm_file_to_image(base->mlx, \
	"./assets/exit.xpm", &base->img.img_width, &base->img.img_height);
	base->img.player = mlx_xpm_file_to_image(base->mlx, \
	"./assets/player.xpm", &base->img.img_width, &base->img.img_height);
	base->img.collectible = mlx_xpm_file_to_image(base->mlx, \
	"./assets/collectible.xpm", &base->img.img_width, &base->img.img_height);
}

int	main(int ac, char *av[])
{
	t_base	*base;

	if (check_arg(ac, av) == 0)
		return (0);
	base = malloc(sizeof(t_base));
	if (!base)
		return (0);
	g_nb_move = 0;
	base->map = get_map(av[1]);
	if (check_valid_map(base->map) == 0)
	{
		free(base->map);
		free(base);
		return (0);
	}
	base->mlx = mlx_init();
	base->win = mlx_new_window(base->mlx, win_size(base->map, 'y') \
	* 64, win_size(base->map, 'x') * 64, "so_long");
	set_assets(base);
	display_game(base, 0, 0, 0);
	mlx_key_hook(base->win, dispatch, base);
	mlx_hook (base->win, 17, (1L << 2), close_win, base);
	mlx_loop(base->mlx);
	return (1);
}
