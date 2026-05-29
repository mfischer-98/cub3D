/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:43:25 by mefische          #+#    #+#             */
/*   Updated: 2026/05/29 15:26:20 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Checks number of arguments */
int	check_number(int n)
{
	if (n != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	return (0);
}

/* Checks if we can open the file */
int	check_fd(char *file_name, char c)
{
	int	fd;

	fd = open(file_name, O_RDWR);
	if (fd < 0 && c == 'm')
	{
		printf("Error\nInvalid map file\n");
		return (1);
	}
	else if (fd < 0 && c == 't')
	{
		printf("Error\nInvalid texture path\n");
		return (1);
	}
	close(fd);
	return (0);
}

/* Checks if map has the .cub extension */
int	check_map_name(char *name)
{
	int	i;

	i = 0;
	if (ft_strrchr(name, '/'))
	{
		name = ft_strrchr(name, '/');
		name++;
	}
	if (!ft_strncmp(name, ".cub", 5))
	{
		printf("Error\nInvalid map name\n");
		return (1);
	}
	name = ft_strrchr(name, '.');
	if (!ft_strncmp(&name[i], ".cub", 5))
		return (0);
	printf("Error\nInvalid map name\n");
	return (1);
}
