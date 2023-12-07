/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:13:16 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/18 14:02:08 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	include_expanded_list(t_lexing *ltable,
	t_lexing *expand, t_token *browse)
{
	t_token		*last;

	last = tk_last(expand->tklist_head);
	if (!browse->prev)
		ltable->tklist_head = expand->tklist_head;
	else
		browse->prev->next = expand->tklist_head;
	if (browse->next)
		browse->next->prev = last;
}

int	format_expands(t_lexing *ltable, t_data_env *data_env)
{
	t_token		*browse;
	t_lexing	expand;

	init_table(&expand);
	browse = ltable->tklist_head;
	while (browse)
	{
		if (!browse->quote && !ft_strmatch(browse->content, "<|>")
			&& (ft_isinbase(' ', browse->content)
				|| ft_isinbase('\t', browse->content)))
		{
			expand.input = browse->content;
			if (!create_token_list(&expand, data_env))
				return (free_structs(ltable, data_env,
						"cannot allocate memory\n", 3));
			include_expanded_list(ltable, &expand, browse);
			tk_delone(browse);
			browse = expand.tklist_head;
		}
		browse = browse->next;
	}
	return (1);
}
