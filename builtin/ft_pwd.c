/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:29:13 by johokyoun         #+#    #+#             */
/*   Updated: 2021/09/11 11:52:18 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

int	builtin_pwd(int i)
{
	char	*path;

	++i;
	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
	return (0);
}
