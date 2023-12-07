/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:30:57 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/17 19:43:59 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_up_quotes(char *oldcontent,
			t_lexing *ltable, t_data_env *data_env)
{
	char	*newcontent;

	if (ft_strlen(oldcontent) < 2)
		return (0);
	newcontent = ft_calloc(sizeof(char), ft_strlen(oldcontent) - 1);
	if (!newcontent)
	{
		free_structs(ltable, data_env, "cannot allocate memory", 3);
		return (0);
	}
	ft_strlcpy(newcontent, oldcontent + 1, ft_strlen(oldcontent) - 1);
	return (newcontent);
}

int	format_tokens(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;
	char	*no_quote_content;

	browse = ltable->tklist_head;
	no_quote_content = 0;
	while (browse)
	{
		if (browse->content && (browse->content[0] == '\''
				|| browse->content[0] == '\"'))
		{
			browse->delim_quote = 1;
			no_quote_content
				= clean_up_quotes(browse->content, ltable, data_env);
			if (!no_quote_content)
				return (1);
			free(browse->content);
			browse->content = no_quote_content;
		}
		browse = browse->next;
	}
	return (1);
}

int	to_expand(t_token *token)
{
	t_token	*browse;

	browse = token;
	if (no_alnum(browse->content) && ft_strncmp(browse->content, "$?", 2))
		return (0);
	if (browse->prev && !ft_strncmp(browse->prev->content, "<<", 2))
		return (0);
	while (browse->prev && browse->join_prev)
	{
		if (browse->prev->prev
			&& !ft_strncmp(browse->prev->prev->content, "<<", 2))
			return (0);
		browse = browse->prev;
	}
	return (1);
}

void	link_joins(t_token *head)
{
	t_token	*browse;

	browse = head;
	if (!browse)
		return ;
	while (browse->next)
	{
		if (browse->next && browse->join_next)
			browse->next->join_prev = 1;
		browse = browse->next;
	}
	while (browse->prev)
	{
		if (browse->prev && browse->join_prev)
			browse->prev->join_next = 1;
		browse = browse->prev;
	}
}

int	expand_token_list(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	link_joins(ltable->tklist_head);
	while (browse)
	{
		if (to_expand(browse))
			browse->content = expand_process(browse->content, data_env);
		if (!browse->content)
			return (free_structs(ltable, data_env,
					"cannot allocate memory\n", 3));
		else if (!browse->content[0])
			browse = tk_delone_and_link(&ltable->tklist_head, browse);
		if (browse)
			browse = browse->next;
	}
	if (!format_tokens(ltable, data_env))
		return (0);
	return (1);
}
