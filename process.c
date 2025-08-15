/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:31:51 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/15 19:47:21 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

void	child_one(t_process *p_1, int *fd)
{
	close(fd[0]);
	dup2(p_1->fd_file, STDIN_FILENO);
	close(p_1->fd_file);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(p_1->path, p_1->cmd, p_1->envp);
}

void	child_two(t_process *p_2, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(p_2->fd_file, STDOUT_FILENO);
	close(p_2->fd_file);
	execve(p_2->path, p_2->cmd, p_2->envp);
}

int	wait_process(t_process *p_1, t_process *p_2, int *fd)
{
	int	status1;
	int	status2;

	status1 = -1;
	status2 = -1;
	close(fd[0]);
	close(fd[1]);
	waitpid(p_1->pid, &status1, 0);
	waitpid(p_2->pid, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (EXIT_FAILURE);
}
