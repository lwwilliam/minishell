/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:56:45 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/13 17:24:44 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_arr(char **command, t_minihell *mini)
{
	int		len;
	int		x;
	char	**tmp;
	t_data	*head;
	t_data	*node;

	x = 0;
	head = NULL;
	while (command[x])
	{
		len = 0;
		while (command[x] && ft_strncmp(command[x], "|", 2))
		{
			len++;
			x++;
		}
		tmp = assign(len, x, command, mini);
		node = lcreate(tmp);
		input_init(&head, node);
		mini->data = head;
		if (!ft_strncmp(command[x], "|", 2))
			++x;
	}
}

char	**assign(int len, int x, char **command, t_minihell *mini)
{
	char	**tmp;
	int		y;
	int		len2;

	y = 0;
	tmp = ft_calloc(len + 1, sizeof(char *));
	len2 = len;
	(void) mini;
	while (len > 0)
	{
		tmp[y] = ft_strdup(command[x - len2]);
		x++;
		y++;
		len--;
	}
	return (tmp);
}

t_data	*lcreate( char **cmd)
{
	t_data	*newlist;

	newlist = (t_data *)malloc(sizeof(t_data));
	newlist->cmd = cmd;
	pipe(newlist->fd);
	newlist->next = NULL;
	newlist->is_last_node = 0;
	return (newlist);
}

void	input_init(t_data **head, t_data *newnode)
{
	t_data	*current;

	if (*head == NULL)
		*head = newnode;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}

void	clear_in(t_data **data)
{
	t_data	*current;
	t_data	*next;

	current = *data;
	while (current != NULL)
	{
		next = current->next;
		free_funct(current->cmd);
		free (current);
		current = next;
	}
	*data = NULL;
}
