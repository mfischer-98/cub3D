/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:17:24 by mefische          #+#    #+#             */
/*   Updated: 2026/07/14 13:32:43 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"

/* Used to check if there are repeated identifiers or missing any */
void	id_count(char id, int *counter)
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

int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

static int	count_tabs(char *str)
{
	int	i;
	int	tabs;

	i = 0;
	tabs = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			tabs++;
		i++;
	}
	return (ft_strlen(str) + (tabs * 3));
}

/* Converts tabs into 4 spaces in string */
char	*convert_tabs(char *str)
{
	int		i;
	int		j;
	char	*temp;

	temp = malloc(sizeof(char) * (count_tabs(str) + 1));
	if (!temp)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\t')
		{
			temp[j++] = ' ';
			temp[j++] = ' ';
			temp[j++] = ' ';
			temp[j++] = ' ';
		}
		else
			temp[j++] = str[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
}
