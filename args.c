/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:10:24 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/16 14:14:46 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

void	init(t_process *p_1, t_process *p_2, char **argv, char **envp)
{
	char	**path;

	path = create_path(envp);
	p_1->cmd = ft_split(argv[2], ' ');
	p_2->cmd = ft_split(argv[3], ' ');
	p_1->path = search_cmd(p_1->cmd, path);
	p_2->path = search_cmd(p_2->cmd, path);
	ft_free_mem(path, 10);
	p_1->fd_file = open(argv[1], O_RDONLY);
	p_2->fd_file = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	p_1->envp = envp;
	p_2->envp = envp;
	//falta verificacao do open aqui
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
	printf("%d\n", i);
	return (path);
}

char	*search_cmd(char **cmd, char **path)
{
	int	i;
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
