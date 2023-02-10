/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:45:39 by wting             #+#    #+#             */
/*   Updated: 2023/02/11 00:01:28 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_count(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == ' ' || !str[i])
		return (0);
	while (str[i] != ' ' && str[i])
	{
		if (str[i] == '"')
			while (str[++i] != '"' && str[i])
				;
		else if (str[i] == '\'')
			while (str[++i] != '\'' && str[i])
				;
		else
			++i;
	}
	return (i);
}

int	word_count(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i++])
	{
		while (str[i] == ' ' && str[i])
			++i;
		++ret;
		while (str[i] != ' ' && str[i])
		{
			if (str[i] == '"')
				while (str[++i] != '"' && str[i])
					;
			else if (str[i] == '\'')
				while (str[++i] != '\'' && str[i])
					;
			else
				++i;
		}
	}
	return (ret);
}

char	**lexer(char *str)
{
	char	**ret;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (word_count(str) + 1));
	if (!ret)
		return (NULL);
	while (*str)
	{
		if (len_count(str))
		{
			ret[i] = ft_substr(str, 0, len_count(str));
			str += len_count(str);
			++i;
		}
		else
			++str;
	}
	ret[i] = NULL;
	return (ret);
}

// int main(int ac, char **av)
// {
// 	printf("ac: %d\n", ac);
// 	char	**tmp = lexer(av[1]);
// 	char	**start = tmp;
// 	int i = -1;
// 	while (tmp[++i])
// 		printf("%s\n", tmp[i]);
// 	i = -1;
// 	while (tmp[++i])
// 		free(tmp[i]);
// 	free (start);
// 	// system("leaks Minishell");
// }