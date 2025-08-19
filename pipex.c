/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:07:34 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/17 13:56:39 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_process	*p_1;
	t_process	*p_2;

	if (argc != 5)
		free_exit(NULL, NULL, 1, NULL);
	p_1 = malloc(sizeof(t_process));
	if (!p_1)
		return (1);
	p_2 = malloc(sizeof(t_process));
	if (!p_2)
	{
		free_all(p_1);
		return (1);
	}
	get_args(p_1, p_2, argv, envp);
	init_child(p_1, p_2);
	return (0);
}
