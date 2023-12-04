/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:42:49 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:38:21 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	meet_special(char c)
{
	if (c == '|')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (ft_isspace(c))
		return (1);
	return (0);
}

int	in_quote(char c, char *q, int *i)
{
	if (c == '\'' || c == '\"')
	{
		if (*q == 0)
			(*q) = c;
		else if (c == *q)
			(*q) = 0;
		(*i) += 1;
	}
	else if (*q != 0)
		(*i) += 1;
	return (*q);
}

void	set_index(int type, int *i, int *start)
{
	if (type == 0)
		(*i) += 1;
	else if (type == 1 || type == 2)
	{	
		(*i) += type;
		(*start) = (*i);
	}
	else if (type == 3)
	{
		(*i) += 1;
		(*start) = (*i);
	}
}
