/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_seperate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:42:06 by wting             #+#    #+#             */
/*   Updated: 2023/03/07 13:05:49 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sep_char(char **str, char seperator)
{
	
}

int	find_set(char c)
{
	char	*charset;
	int		i;
	
	charset = "><|";
	i = 0;
	if (!charset || !c)
		return (0);
	while (charset[i])
	{
		if (charset[i] == c)
			return (charset[i]);
		++i;
	}
	return (0);
}

char	*seperate(char *str, t_minihell mini)
{
	int		i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '"')
			while (str[++i] && str[i] != '"')
				;
		if (findset(str[i]))
		{
			
		}
	}
}
