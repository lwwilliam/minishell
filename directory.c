/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:38:03 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/06 19:22:53 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	printf("%s\n", pwd);
	free(pwd);
}

void	assign_oldpwd(t_env *env_ll, char *pwd, t_minihell *mini)
{
	char	*key;

	while (env_ll != NULL)
	{
		if (!ft_strncmp(env_ll->key, "OLDPWD", 6))
		{
			free(env_ll->value);
			env_ll->value = pwd;
			return ;
		}
		env_ll = env_ll->next;
	}
	key = ft_strdup("OLDPWD");
	add_node_end(mini->env_ll, key, pwd, 0);
}

void	pwd_update(t_env *env_ll, char *new_pwd, t_minihell *mini)
{
	char	*key;

	while (env_ll != NULL)
	{
		if (!ft_strncmp(env_ll->key, "PWD", 3))
		{
			free(env_ll->value);
			env_ll->value = new_pwd;
			return ;
		}
		env_ll = env_ll->next;
	}
	key = ft_strdup("PWD");
	add_node_end(mini->env_ll, key, new_pwd, 0);
}

void	home(t_minihell *mini)
{
	char	*new_dir;

	new_dir = get_env(mini->env_ll, "HOME");
	if (!new_dir[0])
		printf("bash: cd: HOME not set\n");
	chdir(new_dir);
}

void	change_dir(t_minihell *mini)
{
	char	*new_dir;
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (!mini->input_arr[1])
		home(mini);
	else if (!ft_strncmp(mini->input_arr[1], "~", 2))
		chdir(getenv("HOME"));
	else if (!ft_strncmp(mini->input_arr[1], "-", 2))
	{
		new_dir = get_env(mini->env_ll, "OLDPWD");
		if (chdir(new_dir) == -1 && !new_dir[0])
			printf("Minishell: cd: OLDPWD not set\n");
		else
			printf("%s\n", new_dir);
	}
	else if (chdir(mini->input_arr[1]) == -1)
		printf("Minishell: cd: %s: No such file or directory\n",
			mini->input_arr[1]);
	assign_oldpwd(mini->env_ll, pwd, mini);
	pwd = getcwd(NULL, 1024);
	pwd_update(mini->env_ll, pwd, mini);
}
