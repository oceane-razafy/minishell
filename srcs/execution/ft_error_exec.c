/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:25:18 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/17 15:07:40 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_no_such_file(char *file)
{
	write(2, file, ft_strlen(file));
	write(2, ": No such file or directory\n", 28);
}

void	ft_error_cmd_not_found(t_minishell *mini)
{
	struct stat		f_stat;

	if (ft_srch('/', mini->cmd.first_arg) != -1)
	{
		if (stat(mini->cmd.first_arg, &f_stat) == -1)
		{
			perror("");
			ft_exit_exec(127, mini);
		}
		if (S_ISDIR(f_stat.st_mode))
		{
			write(2, mini->cmd.first_arg, ft_strlen(mini->cmd.first_arg));
			write(2, ": Is a directory\n", 17);
			ft_exit_exec(126, mini);
		}
		write(2, "Permission denied\n", 18);
		ft_exit_exec(126, mini);
	}
	if (ft_strcmp(".", mini->cmd.first_arg) == 0)
		ft_filename_required(mini);
	write(2, mini->cmd.first_arg, ft_strlen(mini->cmd.first_arg));
	write(2, ": command not found\n", 20);
	ft_exit_exec(127, mini);
}

void	ft_filename_required(t_minishell *mini)
{
	write(2, ".: filename argument required\n", 30);
	ft_exit_exec(2, mini);
}

void	ft_error_cmd_not_found2(t_minishell *mini)
{
	if (ft_strcmp(".", mini->cmd.cmd_path) == 0)
		ft_filename_required(mini);
	write(2, mini->cmd.cmd_path, ft_strlen(mini->cmd.cmd_path));
	write(2, ": command not found\n", 20);
	ft_exit_exec(127, mini);
}

void	ft_error(int status, t_minishell *mini)
{
	perror("");
	ft_free_all_exec(mini);
	exit(status);
}
