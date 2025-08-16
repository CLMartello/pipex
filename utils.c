/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:41:24 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/16 20:18:29 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/*
void	error_msg(void)
{
	ft_putstr_fd("Invalid number of arguments.\n", 2);
	exit(EXIT_FAILURE);
}*/

void	free_all(t_process *p_1)
{
	int	i;

	i = 0;
	if (p_1->cmd)
	{
		while (p_1->cmd[i] != NULL)
			i++;
		if (p_1->cmd)
			ft_free_mem(p_1->cmd, i - 1);
	}
	if (p_1->path)
		free(p_1->path);
	if (p_1)
		free(p_1);
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

void	free_exit(t_process *p_1, t_process *p_2, int error, char *name)
{
	if (error == 1)
		print_error("Invalid number of arguments.", name);
	else if (error == 2)
		print_error("zsh: permission denied:", name);
	else if (error == 3)
		print_error("zsh: command not found: ", name);
	else if (error == 4)
		print_error("zsh: no such file or directory: ", name);
	else if (error == 5)
	{
		close(p_1->fd_file);
		print_error("zsh: no such file or directory: ", name);
	}
	if (p_1)
		free_all(p_1);
	if (p_2)
		free_all(p_2);
	exit(EXIT_FAILURE);
}
