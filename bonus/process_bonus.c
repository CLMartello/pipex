/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:31:51 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/19 22:24:59 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_h_pipex.h"

pid_t	child(t_process *p, char *command)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		close_fd(fd);
	pid = fork();
	if (pid == -1)
		close_fd(fd);
	else if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd);
		execute(p, fd, command);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd);
	}
	return (pid);
}

void	execute(t_process *p, int *fd, char *command)
{
	if (command[0] == '\0')
	{
		close_fd(fd);
		free_exit(p, 2, NULL);
	}
	p->cmd = ft_split(command, ' ');
	p->path = search_cmd(p->cmd, p->all_path);
	if (!p->path)
	{
		close_fd(fd);
		free_exit(p, 3, p->cmd[0]);
	}
	execve(p->path, p->cmd, p->envp);
	ft_free_mem(p->cmd, 2);
	free(p->path);
}

void	last_child(t_process *p, char *outfile)
{
	p->fd_1 = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p->fd_1 == -1)
		free_exit(p, 5, outfile);
	dup2(p->fd_1, STDOUT_FILENO);
	close(p->fd_1);
	execute(p, NULL, p->argv[p->argc - 2]);
}

void	wait_process(t_process *p)
{
	int	i;

	i = 0;
	while (i < p->count_pid)
	{
		waitpid(p->pid[i], NULL, 0);
		i++;
	}
	free(p->pid);
	free(p);
}
