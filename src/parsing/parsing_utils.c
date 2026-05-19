/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:17:24 by mefische          #+#    #+#             */
/*   Updated: 2026/05/19 17:21:56 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Checks if characters are the correct identifiers
int is_identifier_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (1);
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (1);
	if (line[i] == 'W' && line[i + 1] == 'E')
		return (1);
	if (line[i] == 'E' && line[i + 1] == 'A')
		return (1);
	if (line[i] == 'F')
		return (1);
	if (line[i] == 'C')
		return (1);
	printf("Error\nInvalid identifier characters\n");
	return (0);
}