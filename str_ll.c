/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:22:51 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/14 20:21:00 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*list_create( char *key, char *value)
{
	t_env	*newlist;

	newlist = (t_env *)malloc(sizeof(t_env));
	newlist->value = value;
	newlist->key = key;
	newlist->next = NULL;
	return (newlist);
}

void	insert(t_env **link, t_env *newlist)
{
	newlist->next = *link;
	*link = newlist;
}
