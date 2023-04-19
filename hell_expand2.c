/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_expand2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:23:24 by wting             #+#    #+#             */
/*   Updated: 2023/04/13 18:37:04 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tilde_expand_helper(char *str, t_minihell *mini)
{
	char	*tmp1;
	char	*tmp2;
	char	*sub;
	char	*ret;
	int		i;

	i = -1;
	(void) mini;
	while (str[++i] && str[i] != '~')
		;
	tmp1 = ft_substr(str, 0, i);
	sub = ft_substr(str, i + 1, ft_strlen(getenv("HOME")));
	tmp2 = strjoin_helper(tmp1, getenv("HOME"), 1, 0);
	free (sub);
	tmp1 = ft_substr(str, ft_strlen(getenv("HOME")), ft_strlen(str));
	ret = strjoin_helper(tmp2, tmp1, 1, 1);
	return (ret);
}

void	exp_tilde(int *i, int *count, char **ret, t_minihell *mini)
{
	char	*tmp;
	char	*str;

	str = mini->yes;
	if (*i == 0 && str[*i] == '~' && (!str[*i + 1] || str[*i + 1] == ' '))
	{
		*ret = tilde_expand_helper(str, mini);
		++*count;
	}
	else if (str[*i] == '~' && !*count && (!str[*i + 1] || str[*i + 1] == ' '))
	{
		*ret = tilde_expand_helper(str, mini);
		++*count;
	}
	else if (str[*i] == '~' && (!str[*i + 1] || str[*i + 1] == ' '))
	{
		tmp = tilde_expand_helper(*ret, mini);
		free (*ret);
		*ret = ft_strdup(tmp);
		free (tmp);
		++*count;
	}
}

char	*expand_tilde(char *str, t_minihell *mini)
{
	int		i;
	char	*ret;
	int		count;

	ret = NULL;
	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '"')
			while (str[++i] && str[i] != '"')
				;
		exp_tilde(&i, &count, &ret, mini);
	}
	if (!ret)
		ret = ft_strdup(str);
	return (ret);
}

void	esl(t_minihell *mini)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = expand_tilde(mini->yes, mini);
	free(mini->yes);
	mini->yes = ft_strdup(tmp2);
	tmp = expand(tmp2, mini);
	free (mini->yes);
	free (tmp2);
	tmp2 = seperate(tmp);
	free(tmp);
	mini->term_in = lexer(tmp2, mini);
	free(tmp2);
}
