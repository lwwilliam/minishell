/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:38:03 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/14 21:32:57 by lwilliam         ###   ########.fr       */
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

char	*get_env(t_env *env_ll, char *what)
{
	int		x;
	char	*tmp;
	char	*the_value;

	x = 0;
	tmp = " ";
	while (env_ll != NULL)
	{
		if (!ft_strncmp(env_ll->key, what, ft_strlen(what)))
			tmp = env_ll->value;
		env_ll = env_ll->next;
	}
	if (tmp)
	{
		the_value = malloc(sizeof(char) * ft_strlen(tmp));
		while (tmp[x])
		{
			the_value[x] = tmp[x];
			x++;
		}
	}
	the_value[x] = '\0';
	return (the_value);
}

// void	assign_oldpwd(t_minihell *mini)
// {
// 	char	*old_dir;

// 	old_dir = getcwd(NULL, 1024);

// }

void	change_dir(t_minihell *mini)
{
	int		x;
	char	*new_dir;

	x = 0;
	// assign_oldpwd(mini);
	if (!mini->input_arr[1] || !ft_strncmp(mini->input_arr[1], "~", 1))
	{
		new_dir = get_env(mini->env_ll, "HOME");
		chdir(new_dir);
		free(new_dir);
	}
	else if (!ft_strncmp(mini->input_arr[1], "-", 1))
	{
		new_dir = get_env(mini->env_ll, "OLDPWD");
		printf("%s\n", new_dir);
		if (chdir(new_dir) == -1)
			printf("Minishell: cd: OLDPWD not set\n");
		free(new_dir);
	}
	else if (chdir(mini->input_arr[1]) == -1)
	{
		printf("Minishell: cd: %s: No such file or directory\n",
			mini->input_arr[1]);
	}
}
