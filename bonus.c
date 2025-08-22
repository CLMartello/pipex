/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:41:52 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/22 13:09:06 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_process	*p;

	if (argc < 5)
		free_exit(NULL, 1, NULL);
	p = malloc(sizeof(t_process));
	if (!p)
		free_exit(NULL, 6, NULL);
	init_p(p, argc, argv, envp);
	dup2(p->fd_in, STDIN_FILENO);
	close(p->fd_in);
	while (p->count_cmd < (argc - 2))
	{
		p->pid[p->count_pid] = child(p, argv[p->count_cmd]);
		p->count_pid++;
		p->count_cmd++;
	}
	p->pid[p->count_pid++] = fork();
	if (p->pid[p->count_pid - 1] == 0)
		last_child(p, argv[argc -1]);
	wait_process(p);
	return (0);
}
