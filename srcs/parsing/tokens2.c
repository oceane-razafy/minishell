/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:52:25 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/15 16:31:55 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tk_add_back(t_token **head, t_token *new)
{
	t_token	*browse;

	if (!head || !new)
		return ;
	browse = *head;
	if (*head)
	{
		browse = tk_last(*head);
		browse->next = new;
		new->prev = browse;
	}
	else
		*head = new;
}

void	tk_addto(t_token **head, t_token *new, int pos)
{
	t_token	*browse;
	int		count;

	if (!head || !*head || !new || pos <= 0 || pos > tk_size(*head))
		return ;
	count = 0;
	browse = *head;
	while (++count < pos && browse)
		browse = browse->next;
	new->next = browse->next;
	browse->next = new;
	new->prev = browse;
	if (new->next)
		new->next->prev = new;
}

void	tk_moveto(t_token **head, t_token *token, int pos)
{
	if (!head || pos < 0 || pos > tk_size(*head) || (!*head && pos))
		return ;
	if (token->next)
		token->next->prev = token->prev;
	if (token->prev)
		token->prev->next = token->next;
	token->prev = 0;
	token->next = 0;
	tk_addto(head, token, pos);
}

t_token	*link_tokens(t_token **head, t_token *token, t_token *ret)
{
	if (!token->next && token->prev)
	{
		token->prev->next = 0;
		ret = token->prev;
	}
	else if (token->next && !token->prev)
	{
		*head = token->next;
		token->next->prev = 0;
		ret = *head;
	}
	else if (!token->prev && !token->next)
	{
		tk_delone(token);
		g_mini.exit_status = 0;
		*head = ret;
		return (0);
	}
	else if (token->next && token->prev)
	{
		token->prev->next = token->next;
		token->next->prev = token->prev;
		ret = token->prev;
	}
	return (ret);
}

t_token	*tk_delone_and_link(t_token **head, t_token *token)
{
	t_token	*ret;

	ret = 0;
	if (!token || !head || !*head)
		return (0);
	ret = link_tokens(head, token, ret);
	if (!ret)
		return (0);
	tk_delone(token);
	return (ret);
}
