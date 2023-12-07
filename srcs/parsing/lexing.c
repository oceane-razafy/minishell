/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:22:11 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/18 16:08:26 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_redir_token(t_lexing *ltable, t_data_env *data_env, int *reader)
{
	t_token	*new;
	char	redir;

	new = 0;
	redir = ltable->input[*reader];
	if (ltable->input[*reader + 1])
	{
		if (ltable->input[*reader + 2]
			&& ft_isinbase(ltable->input[*reader + 2], "|"))
			return (free_structs(ltable, data_env,
					"syntax error near redirection\n", 1));
	}
	if (ltable->input[*reader + 1] == redir)
	{
		new = tk_new(ft_substr(ltable->input, *reader, 2));
		*reader = *reader + 1;
	}
	else
		new = tk_new(ft_substr(ltable->input, *reader, 1));
	if (!new->content)
		return (free_structs(ltable, data_env,
				"cannot allocate memory\n", 3));
	tk_add_back(&ltable->tklist_head, new);
	*reader = *reader + 1;
	return (1);
}

int	find_quote_len(t_lexing *ltable, int reader, char quote_char)
{
	int	count;

	count = 2;
	while (ltable->input[++reader] && ltable->input[reader] != quote_char)
		count++ ;
	if (ltable->input[reader] == 0)
		return (0);
	return (count);
}

int	create_quoted_token(t_lexing *ltable, t_data_env *data_env, int *reader)
{
	t_token	*new;
	char	quote_char;
	int		quote_len;

	new = 0;
	quote_char = ltable->input[*reader];
	quote_len = find_quote_len(ltable, *reader, quote_char);
	if (!quote_len)
		return (free_structs(ltable, data_env, "syntax error\n", 1));
	new = tk_new(ft_substr(ltable->input, *reader, quote_len));
	if (!new->content)
		return (free_structs(ltable, data_env,
				"cannot allocate memory\n", 3));
	new->quote = 1;
	tk_add_back(&ltable->tklist_head, new);
	define_joins(ltable, new, *reader, quote_len);
	*reader += quote_len;
	return (1);
}

int	create_regular_token(t_lexing *ltable,
			t_data_env *data_env, int *reader)
{
	t_token	*new;
	int		count;

	new = 0;
	count = 0;
	while (ltable->input[*reader + count]
		&& !ft_isinbase(ltable->input[*reader + count], "<|>\'\" \t"))
		count++ ;
	new = tk_new(ft_substr(ltable->input, *reader, count));
	if (!new->content)
		return (free_structs(ltable, data_env,
				"cannot allocate memory\n", 3));
	tk_add_back(&ltable->tklist_head, new);
	*reader += count;
	return (1);
}

int	create_token_list(t_lexing *ltable, t_data_env *data_env)
{
	int		reader;

	reader = 0;
	while (ltable->input[reader])
	{
		while (ltable->input[reader] == ' ' || ltable->input[reader] == '\t')
			reader++;
		if (ltable->input[reader] && ft_isinbase(ltable->input[reader], "<|>"))
			if (!create_redir_token(ltable, data_env, &reader))
				return (0);
		while (ltable->input[reader] && (ltable->input[reader] == ' '
				|| ltable->input[reader] == '\t'))
			reader++;
		if (ltable->input[reader] && ft_isinbase(ltable->input[reader], "\'\""))
			if (!create_quoted_token(ltable, data_env, &reader))
				return (0);
		while (ltable->input[reader] && (ltable->input[reader] == ' '
				|| ltable->input[reader] == '\t'))
			reader++;
		if (ltable->input[reader]
			&& !ft_isinbase(ltable->input[reader], "<|>\'\""))
			if (!create_regular_token(ltable, data_env, &reader))
				return (0);
	}
	return (1);
}
