/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_h_pipex.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:15:10 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/19 22:27:40 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H_PIPEX_H

# define BONUS_H_PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_process
{
	pid_t	*pid;
	int		count_pid;
	int		count_cmd;
	int		fd_0;
	int		fd_1;
	char	**cmd;
	char	*path;
	char	**all_path;
	int		argc;
	char	**argv;
	char	**envp;
}			t_process;

//Strings functions
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	**ft_free_mem(char **result, int i);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);

//Parse functions
void	init_p(t_process *p, int argc, char **argv, char **envp);
char	**create_path(char **path);
char	*search_cmd(char **cmd, char **path);

//Process functions
void	init_child(t_process *p_1, t_process *p_2);
pid_t	child(t_process *p, char *command);
void	execute(t_process *p, int *fd, char *command);
void	last_child(t_process *p, char *outfile);
void	wait_process(t_process *p);

//Utils functions
void	free_all(t_process *p_1);
void	free_exit(t_process *p_1, int error, char *name);
void	close_fd(int *fd);

#endif
