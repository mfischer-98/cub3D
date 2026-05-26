/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:17:24 by mefische          #+#    #+#             */
/*   Updated: 2026/05/26 14:44:03 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Used to check if there are repeated identifiers or missing any */
void id_count(char id, int *counter)
{
	if (id == 'N')
		counter[0]++;
	else if (id == 'S')
		counter[1]++;
	else if (id == 'W')
		counter[2]++;
	else if (id == 'E')
		counter[3]++;
	else if (id == 'F')
		counter[4]++;
	else if (id == 'C')
		counter[5]++;
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\r')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

void	line_trim(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\r') && (str[i + 1] == '\n'))
			str[i] = '\0';
		else if ((str[i] == '\n') && (str[i + 1] == '\0'))
			str[i] = '\0';
		i++;
	}
}

int	line_len(char *str)
{
	int	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}
