/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:29:29 by johokyoun         #+#    #+#             */
/*   Updated: 2021/09/12 21:14:44 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(int i)
{
	int		j;
	bool	flag;

	j = 0;
	flag = false;
	if (g_info.cmds[i][1] == NULL)
		return (0);
	while (g_info.cmds[i][j])
	{
		if (ft_strchr(g_info.cmds[i][j], '=') != NULL)
		{
			print_error(UNSET_ARG_ERROR, g_info.cmds[i][j]);
			flag = true;
		}
		find_key_and_unset(g_info.cmds[i][j]);
		j++;
	}
	if (flag == true)
		return (1);
	return (0);
}
