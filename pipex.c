/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:07:34 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/15 19:05:24 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	int			fd[2];
	t_process	*p_1;
	t_process	*p_2;

	if (argc != 5)
		error_msg();
	p_1 = malloc(sizeof(t_process));
	p_2 = malloc(sizeof(t_process));
	if (!p_1 || !p_2)
		return (1);
	init(p_1, p_2, argv, envp);
	if (pipe(fd) == -1)
		return (1);
	p_1->pid = fork();
	if (p_1->pid == -1)
		return (1);
	else if (p_1->pid == 0)
		child_one(p_1, fd);
	p_2->pid = fork();
	if (p_2->pid == -1)
		return (1);
	else if (p_2->pid == 0)
		child_two(p_2, fd);
	wait_process(p_1, p_2, fd);
	return (0);
}
