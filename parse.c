/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:10:24 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/16 20:19:24 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

void	init_p(t_process *p_1, t_process *p_2)
{
	p_1->cmd = NULL;
	p_1->path = NULL;
	p_1->envp = NULL;
	p_2->cmd = NULL;
	p_2->path = NULL;
	p_2->envp = NULL;
}

void	get_args(t_process *p_1, t_process *p_2, char **argv, char **envp)
{
	char	**path;

	init_p(p_1, p_2);
	p_1->fd_file = open(argv[1], O_RDONLY);
	if (p_1->fd_file == -1)
		free_exit(p_1, p_2, 4, argv[1]);
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
		free_exit(p_1, p_2, 2, NULL);
	path = create_path(envp);
	p_1->cmd = ft_split(argv[2], ' ');
	p_2->cmd = ft_split(argv[3], ' ');
	p_1->path = search_cmd(p_1->cmd, path);
	p_2->path = search_cmd(p_2->cmd, path);
	ft_free_mem(path, 10);
	if (!p_1->path)
		free_exit(p_1, p_2, 3, p_1->cmd[0]);
	if (!p_2->path)
		free_exit(p_1, p_2, 3, p_2->cmd[0]);
	p_2->fd_file = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p_2->fd_file == -1)
		free_exit(p_1, p_2, 5, argv[4]);
	p_1->envp = envp;
	p_2->envp = envp;
}

char	**create_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
		}
		i++;
	}
	i = 0;
	while (path[i] != NULL)
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	return (path);
}

char	*search_cmd(char **cmd, char **path)
{
	int		i;
	char	*real_path;

	i = 0;
	while (path[i] != 0)
	{
		real_path = ft_strdup((const char *)path[i]);
		real_path = ft_strjoin(real_path, cmd[0]);
		if ((access(real_path, F_OK | X_OK)) == 0)
		{
			return (real_path);
		}
		free(real_path);
		i++;
	}
	return (NULL);
}
