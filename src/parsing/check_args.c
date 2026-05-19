/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:43:25 by mefische          #+#    #+#             */
/*   Updated: 2026/05/19 15:07:23 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_number(int n)
{
	if (n != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	return (0);
}

int	check_fd(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR);
	if (fd < 0)
	{
		ft_printf("Error\nInvalid map file\n");
		return (1);
	}
	close(fd);
	return (0);
}

int	check_mapname(char *name)
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
		ft_printf("Error\nInvalid map name\n");
		return (0);
	}
	name = ft_strrchr(name, '.');
	if (!ft_strncmp(&name[i], ".cub", 5))
		return (1);
	ft_printf("Error\nInvalid map name\n");
	return (0);
}
