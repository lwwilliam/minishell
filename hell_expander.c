/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:07:55 by wting             #+#    #+#             */
/*   Updated: 2023/02/17 14:26:14 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*call_helper(char *str, int *i, )
// {
	
// }

// char	*expand(char *str, t_minihell *mini)
// {
// 	int		i;
// 	char	*ret;
// 	int		count;
// 	char	*tmp;

// 	ret = NULL;
// 	tmp = NULL;
// 	count = 0;
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '\'')
// 		{
// 			while (str[++i] && str[i] != '\'')
// 				;
// 		}
// 		if (str[i] == '"')
// 		{
// 			while (str[++i] && str[i] != '"')
// 			{
// 				if (str[i] == '$' && count == 0)
// 				{
// 					ret = expand_helper(str, mini);
// 					++count;
// 				}
// 				else if (str[i] == '$')
// 				{
// 					tmp = expand_helper(ret, mini);
// 					free (ret);
// 					ret = ft_strdup(tmp);
// 					free (tmp);
// 					++count;
// 				}
// 			}
// 		}
// 		if (str[i] == '$' && count == 0)
// 		{
// 			ret = expand_helper(str, mini);
// 			++count;
// 		}
// 		else if (str[i] == '$')
// 		{
// 			tmp = expand_helper(ret, mini);
// 			free (ret);
// 			ret = ft_strdup(tmp);
// 			free (tmp);
// 			++count;
// 		}
// 	}
// 	if (!ret)
// 		ret = ft_strdup(str);
// 	return (ret);
// }

// static char	*expand_quotes(char *str, int *i)
// {
// 	while (str[++(*i)] && str[*i] != '\'')
// 		;
// 	return (ft_substr(str, *i + 1, ft_strlen(str)));
// }

// static char	*expand_dollar(char *str, int *i, t_minihell *mini)
// {
// 	char	*ret;

// 	ret = expand_helper(str + (*i), mini);
// 	*i += ft_strlen(ret);
// 	return (ret);
// }

// static char	*expand_double_quotes(char *str, int *i, t_minihell *mini)
// {
// 	char	*ret;
// 	char	*tmp;
// 	int		count;

// 	ret = NULL;
// 	tmp = NULL;
// 	count = 0;
// 	while (str[++(*i)] && str[*i] != '"')
// 	{
// 		if (str[*i] == '$' && count == 0)
// 			ret = expand_dollar(str, i, mini);
// 		else if (str[*i] == '$')
// 		{
// 			tmp = expand_dollar(str, i, mini);
// 			free(ret);
// 			ret = ft_strdup(tmp);
// 			free(tmp);
// 		}
// 	}
// 	return (ret);
// }

// static char	*perform_expansion(char *str, t_minihell *mini)
// {
// 	int		i;
// 	char	*ret;

// 	i = -1;
// 	ret = NULL;
// 	while (str[++i])
// 	{
// 		if (str[i] == '\'')
// 			str = expand_quotes(str, &i);
// 		if (str[i] == '"')
// 		{
// 			ret = expand_double_quotes(str, &i, mini);
// 			if (ret != NULL)
// 				break ;
// 		}
// 		if (str[i] == '$' && (i == 0 || str[i - 1] != '\\'))
// 			ret = expand_dollar(str, &i, mini);
// 	}
// 	return (ret);
// }

// char	*expand(char *str, t_minihell *mini)
// {
// 	char	*expanded_str;

// 	expanded_str = perform_expansion(str, mini);
// 	if (!expanded_str)
// 		return (ft_strdup(str));
// 	return (expanded_str);
// }