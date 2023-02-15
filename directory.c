/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:38:03 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/15 11:42:46 by lwilliam         ###   ########.fr       */
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

void	assign_oldpwd(t_env *env_ll, char *old_pwd)
{
	while (env_ll != NULL)
	{
		if(!ft_strncmp(env_ll->key, "OLDPWD", 6))
			env_ll->value = old_pwd;
		env_ll = env_ll->next;
	}
}

void	change_dir(t_minihell *mini)
{
	char	*new_dir;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 1024);
	if (!mini->input_arr[1] || !ft_strncmp(mini->input_arr[1], "~", 1))
	{
		new_dir = get_env(mini->env_ll, "HOME");
		chdir(new_dir);
		free(new_dir);
	}
	else if (!ft_strncmp(mini->input_arr[1], "-", 1))
	{
		new_dir = get_env(mini->env_ll, "OLDPWD");
		if (chdir(new_dir) == -1 && !ft_strncmp(new_dir, "(null)", 7))
			printf("Minishell: cd: OLDPWD not set\n");
		else
			printf("%s\n", new_dir);
		free(new_dir);
	}
	else if (chdir(mini->input_arr[1]) == -1)
		printf("Minishell: cd: %s: No such file or directory\n",
			mini->input_arr[1]);
	assign_oldpwd(mini->env_ll, old_pwd);
}
