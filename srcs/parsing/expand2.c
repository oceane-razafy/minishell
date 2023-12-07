/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:50:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/15 16:30:55 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_with_error_code(char *content, char **cursor)
{
	char	*error_code;
	int		content_len;
	char	*new_content;

	error_code = ft_itoa(g_mini.exit_status);
	if (!error_code)
		return (0);
	content_len = ft_strlen(content) + ft_strlen(error_code) - 1;
	new_content = ft_calloc(sizeof(char), content_len);
	if (!new_content)
		return (0);
	update_with_error(new_content, content, error_code, cursor);
	free(error_code);
	free(content);
	return (new_content);
}

char	*delete_name(char *content, char **cursor, int name_len)
{
	char	*new_content;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new_content = ft_calloc(sizeof(char), ft_strlen(content) - name_len);
	if (!new_content)
		return (0);
	while (*(content + ++i) && content + i != *cursor)
	{
		new_content[j] = content[i];
		j++;
	}
	i++;
	while (*(content + i) && ft_isalnum(*(content + i)))
		i++;
	*cursor = new_content + j;
	copy_content_end(new_content, content, i, j);
	free(content);
	return (new_content);
}

char	*get_new_content(char *content, char **cursor, int name_len, char **env)
{
	if (*cursor && **cursor && (*cursor + 1)[0] == '?')
		content = replace_with_error_code(content, cursor);
	else if (*cursor && **cursor && !ft_isalnum((*cursor + 1)[0]))
	{
		*cursor = *(cursor) + 1;
		while (**cursor && **cursor != '$')
			*cursor = *(cursor) + 1;
		return (content);
	}
	else if (*cursor && **cursor && ft_isinbase((*cursor + 1)[0], "0123456789"))
		content = delete_num(content, cursor);
	else if (!*env || !**env)
		content = delete_name(content, cursor, name_len);
	else if (name_len)
		content = replace_with_value(content, cursor, name_len, env);
	if (!content)
		return (0);
	return (content);
}

char	*expand_variable(char *content, t_data_env *data_env)
{
	char	*cursor;
	char	**env;
	int		name_len;

	cursor = content;
	while (cursor && *cursor)
	{
		name_len = 0;
		env = data_env->envp;
		while (cursor && *cursor && *cursor != '$')
			cursor++;
		while (*cursor && *(cursor + name_len + 1)
			&& (ft_isalnum(*(cursor + name_len + 1))))
			name_len++;
		while (name_len && env && *env
			&& ft_strenvcmp(cursor + 1, *env, name_len) != 0)
			env++;
		content = get_new_content(content, &cursor, name_len, env);
		if (!content)
			return (0);
	}
	return (content);
}

char	*expand_process(char *content, t_data_env *data_env)
{
	if (ft_isinbase('$', content) && content[0] != '\'')
	{
		content = expand_variable(content, data_env);
		if (!content)
			return (0);
	}
	return (content);
}
