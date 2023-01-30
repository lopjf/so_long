/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:14:04 by loris             #+#    #+#             */
/*   Updated: 2022/10/31 00:02:12 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	win_size(char *map, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (c == 'x')
	{
		ret = 1;
		while (map[i] != '\0')
			if (map[i++] == '\n')
				ret++;
	}
	else if (c == 'y')
		while (map[ret] != '\n' && map[ret] != '\0')
			ret++;
	return (ret);
}

char	*get_map(char *map_name)
{
	int		fd;
	char	*map;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = get_file(fd);
	close(fd);
	return (map);
}

int	check_ext(char *s1)
{
	char	*s2;
	char	*s3;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	if (i < 5)
		return (0);
	i = 0;
	s2 = ft_strdup(&s1[ft_strlen(s1) - 4]);
	s3 = ft_strdup(&s1[ft_strlen(s1) - 5]);
	if (ft_strncmp(s2, ".ber", 4) == 0)
		i = 1;
	if (ft_strncmp(s3, "/.ber", 5) == 0)
		i = 0;
	free(s2);
	free(s3);
	return (i);
}

int	check_arg(int ac, char *av[])
{
	int		fd;

	if (ac != 2)
	{
		ft_printf("Error\nThis program needs 1 argument\n");
		return (0);
	}
	if (check_ext(av[1]) == 0)
	{
		ft_printf("Error\nThis program takes a map in format *.ber\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nThe .ber map does not exist\n");
		return (0);
	}
	close(fd);
	return (1);
}
