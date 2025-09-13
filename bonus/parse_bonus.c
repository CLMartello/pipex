/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:10:24 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/21 14:46:30 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_p(t_process *p, int argc, char **argv, char **envp)
{
	p->count_pid = 0;
	p->cmd = NULL;
	p->path = NULL;
	p->argc = argc;
	p->argv = argv;
	p->envp = envp;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		fd_heredoc(p, argv);
		p->fd_in = open("tmp_heredoc", O_RDONLY);
		p->count_cmd = 3;
	}
	else
	{
		p->fd_in = open(argv[1], O_RDONLY);
		if (p->fd_in == -1)
			free_exit(p, 4, argv[1]);
		p->count_cmd = 2;
	}
	p->pid = malloc(sizeof(pid_t) * (argc - p->count_cmd) + 1);
	if (!p->pid)
		free_exit(p, 6, NULL);
	p->all_path = create_path(envp);
}

void	fd_heredoc(t_process *p, char **argv)
{
	int		fd;
	char	*line;
	char	*eof;

	fd = open("tmp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		free_exit(p, 4, argv[1]);
	eof = ft_strdup((char *)argv[2]);
	eof = ft_strjoin(eof, "\n");
	while (1)
	{
		ft_putstr_fd("here_doc>", 1);
		line = get_next_line(STDIN_FILENO);
		if ((ft_strncmp(line, eof, ft_strlen(line))) == 0 || !line)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(eof);
	free(line);
	close(fd);
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
