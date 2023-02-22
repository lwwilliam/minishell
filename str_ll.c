/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:22:51 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/22 16:45:27 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*list_create( char *key, char *value)
{
	t_env	*newlist;

	newlist = (t_env *)malloc(sizeof(t_env));
	newlist->value = value;
	newlist->key = key;
	newlist->print = 0;
	newlist->next = NULL;
	return (newlist);
}

void	insert(t_env **link, t_env *newlist)
{
	newlist->next = *link;
	*link = newlist;
}

t_env	*add_node_end(t_env *head, char *key, char *value, int print)
{
	t_env	*new_node;
	t_env	*current_node;

	current_node = head;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->print = print;
	new_node->next = NULL;
	if (head == NULL)
	{
		head = new_node;
		return (head);
	}
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}
	current_node->next = new_node;
	return (head);
}

void	remove_node(t_env **head, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = *head;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key)))
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	remove_head_node(t_env **head)
{
	t_env	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	*head = (*head)->next;
	free(temp->key);
	free(temp->value);
	free(temp);
}
