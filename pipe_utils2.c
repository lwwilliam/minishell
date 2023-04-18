/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:10:34 by wting             #+#    #+#             */
/*   Updated: 2023/04/14 18:18:51 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_no_pipes(t_minihell *mini, t_data *data)
{
	if (mini->ll_len == 1)
	{
		run_heredoc(mini, data);
		command(mini, data, 1);
		term_reset(data);
		return (0);
	}
	return (1);
}