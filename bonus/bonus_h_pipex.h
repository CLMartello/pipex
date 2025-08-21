/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_h_pipex.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:15:10 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/21 11:59:06 by clumertz         ###   ########.fr       */
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

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 10

# endif

typedef struct s_process
{
	pid_t	*pid;
	int		count_pid;
	int		count_cmd;
	int		fd_in;
	int		fd_out;
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
void	ft_putstr_fd(char *s, int fd);
char	*get_next_line(int fd);

//Parse functions
void	init_p(t_process *p, int argc, char **argv, char **envp);
char	**create_path(char **path);
char	*search_cmd(char **cmd, char **path);
void	fd_heredoc(t_process *p, char **argv);

//Process functions
pid_t	child(t_process *p, char *command);
void	execute(t_process *p, int *fd, char *command);
void	last_child(t_process *p, char *outfile);
void	wait_process(t_process *p);

//Utils functions
void	free_all(t_process *p_1);
void	free_exit(t_process *p_1, int error, char *name);
void	close_fd(int *fd);
void	free_db_str(char **db_str);

#endif
