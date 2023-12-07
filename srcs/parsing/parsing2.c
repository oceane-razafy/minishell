/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:04:36 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/10 20:07:08 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_previous_quote(char *content, int i)
{
	if (i < 1)
		return (1);
	while (--i > -1)
	{
		if (ft_isinbase(content[i], "\'\""))
			return (0);
	}
	return (1);
}

int	gen_no_dollars_len(char *content)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	while (content[++i])
	{
		if (content[i] && content[i] == '$'
			&& content[i + 1] && ft_isinbase(content[i + 1], "\'\"")
			&& no_previous_quote(content, i))
		{
			if ((i == 0) || (content[i - 1] && content[i - 1] != '$'))
				i++;
		}
		if (content[i])
			len++;
	}
	return (len);
}

char	*gen_no_dollars(char *content, char *new_content)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (content[++i])
	{
		if (content[i] && content[i] == '$'
			&& content[i + 1] && ft_isinbase(content[i + 1], "\'\"")
			&& no_previous_quote(content, i))
		{
			if ((i == 0) || (content[i - 1] && content[i - 1] != '$'))
				i++;
		}
		if (content[i])
		{
			new_content[j] = content[i];
			j++;
		}
	}
	return (new_content);
}

int	special_char_error(char *content)
{
	if (ft_isinbase(content[0], "#:") && ft_strlen(content) < 2)
		return (0);
	else if (ft_isinbase(content[0], "!") && ft_strlen(content) < 2)
	{
		set_error(1);
		return (0);
	}
	return (1);
}

char	*replace_dollars(char *content)
{
	char	*new_content;
	int		len;
	int		i;

	i = -1;
	if (!special_char_error(content))
		return (0);
	len = gen_no_dollars_len(content);
	new_content = ft_calloc(sizeof(char), len + 1);
	if (!new_content)
		return (0);
	while (content[++i])
	{
		if (content[i] == '$' && (content[i + 1]
				&& ft_isinbase(content[i + 1], "\'\"")))
		{
			new_content = gen_no_dollars(content, new_content);
			if (!new_content)
				return (0);
			free (content);
			return (new_content);
		}
	}
	free (new_content);
	return (content);
}
