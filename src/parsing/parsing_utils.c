/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mefische <mefische@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:17:24 by mefische          #+#    #+#             */
/*   Updated: 2026/05/21 16:06:13 by mefische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
