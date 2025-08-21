/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:41:24 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/21 14:16:23 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_h_pipex.h"

void	free_db_str(char **db_str)
{
	int	i;

	i = 0;
	while (db_str[i] != NULL)
		i++;
	ft_free_mem(db_str, i);
}

void	free_all(t_process *p)
{
	if (p->fd_in)
		close(p->fd_in);
	if (p->cmd)
		free_db_str(p->cmd);
	if (p->path)
		free(p->path);
	if (p->all_path)
		free_db_str(p->all_path);
	if (p)
		free(p);
}

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

static void	print_error(char *msg, char *name)
{
	ft_putstr_fd(msg, 2);
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
}

void	free_exit(t_process *p, int error, char *name)
{
	if (error == 1)
		print_error("Invalid number of arguments.", name);
	else if (error == 2)
		print_error("zsh: permission denied:", name);
	else if (error == 3)
	{
		free(p->pid);
		print_error("zsh: command not found: ", name);
	}
	else if (error == 4)
		print_error("zsh: no such file or directory: ", name);
	else if (error == 5)
		print_error("zsh: no such file or directory: ", name);
	else if (error == 6)
		print_error("Failure on malloc allocation. ", name);
	if (p)
		free_all(p);
	exit(EXIT_FAILURE);
}
