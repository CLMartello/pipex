/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_pipex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:15:10 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/16 14:05:59 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_PIPEX_H

# define H_PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_process
{
	pid_t	pid;
	int		fd_file;
	char	*path;
	char	**cmd;
	char	**envp;
}		t_process;

//Strings functions
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	**ft_free_mem(char **result, int i);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);

//Parse functions
void	init(t_process *p1, t_process *p2, char **argv, char **envp);
char	**create_path(char **path);
char	*search_cmd(char **cmd, char **path);

//Process functions
void	child_one(t_process *p_1, int *fd);
void	child_two(t_process *p_2, int *fd);
int		wait_process(t_process *p_1, t_process *p_2, int *fd);

//Utils functions
void	error_msg(void);
void	free_all(t_process *p_1);

#endif
