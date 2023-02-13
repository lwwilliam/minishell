/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:38:03 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/13 12:52:33 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_dir(t_minihell *mini)
{
	DIR				*d;
	struct dirent	*dir;

	(void)mini;
	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			printf("%s\n", dir->d_name);
		closedir(d);
	}
}

void	what_dir(char *en, int print)
{
	int		x;
	int		y;
	char	*tmp;

	x = 0;
	y = 0;
	tmp = malloc(sizeof(char) * ft_strlen(en) + 1);
	while (en[x] != '=')
		x++;
	x++;
	while (en[x])
		tmp[y++] = en[x++];
	tmp[y] = '\0';
	chdir(tmp);
	if (print == 1)
		printf("%s\n", tmp);
	free(tmp);
}

void	change_dir(t_minihell *mini)
{
	int		x;

	x = 0;
	if (!mini->input_arr[1] || !ft_strncmp(mini->input_arr[1], "~", 1)
		|| !ft_strncmp(mini->input_arr[1], "-", 1))
	{
		while (mini->env_arr[x])
		{
			if (!ft_strncmp(mini->env_arr[x], "HOME", 4) && (!mini->input_arr[1]
					|| !ft_strncmp(mini->input_arr[1], "~", 1)))
				what_dir(mini->env_arr[x], 0);
			if (!ft_strncmp(mini->input_arr[1], "-", 1))
				what_dir(mini->env_arr[x], 1);
			x++;
		}
	}
	else
		if (chdir(mini->input_arr[1]) < 0)
			printf("Minishell: cd: %s: No such file or directory\n",
				mini->input_arr[1]);
}
