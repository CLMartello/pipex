/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:07:34 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/10 13:45:46 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

int	main(int argc, char *argv[])
{
	char	*exec;
	int	fd[2];
	int	fd_input;
	char	buffer[100];
	pid_t	pid;
	

	if (argc != 5)
	{
		perror("Invalid number of arguments.");
		return (1);
	}
//	if (open(argv[1], O_RDONLY) == -1);
//		return (1);
//precisa abrir a leitura do input file
//1st - pipe (fd[0] para read e fd[1] para write)
	if (pipe(fd) == -1)
		return (1);
//	open(argv[1], O_RDONLY);
	fd_input = open("test.txt", O_RDONLY);
//2nd - fork
	pid = fork();
	if (pid == -1)
		return (1);
//pid do child e 0
	if (pid == 0)
	{
		//ler o arquivo de input, usar get next line?
		read(fd_input, buffer, 20);
		//process no fd[0];
		//fd[1] = execve(paths, cmd1, fd[0], NULL);
		//output no fd[1];
		
		close(fd[0]);
	}
//	open(argv[4], O_CREAT, O_WRONLY);
//pid do parent e maior que 0
	if (p > 0)
	{
		//process no fd[1];
		//output_file = execve(paths, cmd2, fd[1], NULL);
		//output no output_file;
		//close(fd[1]);
	}
	close(p);
//	exec = getenv("PATH");
	return (0);
}
