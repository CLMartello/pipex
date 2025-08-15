/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:41:24 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/15 17:51:22 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

void	error_msg(void)
{
	write(2, "Invalid number of arguments.\n", 29);
	exit(EXIT_FAILURE);
}

void	free_all(t_process *p_1, t_process *p_2)
{
	ft_free_mem(p_1->cmd, 1);
	ft_free_mem(p_2->cmd, 1);
	free(p_1->path);
	free(p_2->path);
	free(p_1);
	free(p_2);
}
