/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/18 16:21:11 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_g	g_mini;

int	define_token_types(t_lexing *ltable, t_data_env *data_env, int monitor)
{
	if (!join_quotes(ltable, data_env))
		return (0);
	monitor = define_redirs(ltable);
	if (monitor)
		monitor = define_delims(ltable);
	if (monitor)
		monitor = define_files(ltable);
	if (monitor)
		monitor = define_cmds(ltable, data_env);
	if (monitor)
		define_args(ltable);
	if (!monitor)
		return (0);
	return (1);
}

void	process_input(t_minishell_g *g_mini, t_minishell *mini)
{
	int	monitor;

	monitor = 0;
	mini->ltable.input = replace_dollars(mini->ltable.input);
	if (mini->ltable.input)
		monitor = create_token_list(&mini->ltable, &mini->data_env);
	if (monitor)
		monitor = parse_token_list(&mini->ltable, &mini->data_env);
	if (monitor)
		monitor = parse_redirections(&mini->ltable, &mini->data_env);
	if (monitor)
		monitor = expand_token_list(&mini->ltable, &mini->data_env);
	if (monitor)
		monitor = format_expands(&mini->ltable, &mini->data_env);
	if (monitor)
		monitor = define_token_types(&mini->ltable, &mini->data_env, monitor);
	if (monitor)
		ft_execute(g_mini, mini);
	if (monitor)
		tk_clear(&mini->ltable.tklist_head);
}

void	ft_exit_eof(t_minishell_g *g_mini, t_minishell *mini)
{
	rl_clear_history();
	ft_free_env(mini->data_env.envp, mini->data_env.size);
	free(mini->data_env.pwd);
	printf("exit\n");
	exit(g_mini->exit_status);
}

void	minishell(t_minishell_g *g_mini, t_minishell *mini)
{
	while (1)
	{
		g_mini->status_done = 0;
		mini->ltable.input = readline("minishell$ ");
		if (!mini->ltable.input)
			ft_exit_eof(g_mini, mini);
		if (mini->ltable.input[0] == 0)
			continue ;
		add_history(mini->ltable.input);
		process_input(g_mini, mini);
		free(mini->ltable.input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

	if (envp == NULL)
		return (1);
	(void) argv;
	if (argc != 1)
	{
		write(2, "./minishell doesn't take any arguments\n", 39);
		return (127);
	}
	ft_init_signals();
	ft_init_mini(&g_mini, &mini, envp);
	minishell(&g_mini, &mini);
	return (0);
}
