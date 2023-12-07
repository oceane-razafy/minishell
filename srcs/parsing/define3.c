/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:20:30 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/18 17:09:23 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_cmd_path(char**possible_paths, char *cmd, char *cmd_path)
{
	free_array(possible_paths);
	free (cmd);
	return (cmd_path);
}

char	*find_cmd_path(char	*cmd_name, char **envp)
{
	int		i;
	char	*cmd;
	char	*cmd_path;
	char	**possible_paths;

	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	possible_paths = ft_split(*envp + 5, ':');
	i = -1;
	while (possible_paths[++i])
	{
		cmd = ft_strjoin("/", cmd_name);
		if (!cmd)
			return (0);
		cmd_path = ft_strjoin(possible_paths[i], cmd);
		if (!cmd_path)
			return (0);
		if (access(cmd_path, X_OK) == 0)
			return (ret_cmd_path(possible_paths, cmd, cmd_path));
		free (cmd);
		free (cmd_path);
	}
	free_array(possible_paths);
	return (0);
}

int	check_builtins(t_token *token)
{
	if (ft_strcmp("cd", token->content) == 0)
		return (0);
	else if (ft_strcmp("pwd", token->content) == 0)
		return (0);
	else if (ft_strcmp("unset", token->content) == 0)
		return (0);
	else if (ft_strcmp("env", token->content) == 0)
		return (0);
	else if (ft_strcmp("export", token->content) == 0)
		return (0);
	else if (ft_strcmp("echo", token->content) == 0)
		return (0);
	else if (ft_strcmp("exit", token->content) == 0)
		return (0);
	return (1);
}

int	check_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (0);
	}
	return (1);
}
