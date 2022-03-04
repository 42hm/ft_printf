/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp_util_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:53:19 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/05 01:21:09 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	pf_putstr(char *s, t_info *info, t_data *data)
{
	if (data->prec > 0 && data->len < data->prec)
		data->print_ret += write(1, s, data->len);
	else if (data->prec > 0 && data->len > data->prec)
		data->print_ret += write(1, s, data->prec);
	else if (info->type == POINTER || (info->flag & HASH))
		data->print_ret += write(1, s, 2);
	else
		data->print_ret += write(1, s, data->len);
}

void	pf_strlen(char *s, t_info *info, t_data *data)
{
	if ((info->flag & DOT) && data->prec == 0)
		return ;
	while (s[data->len] != 0)
		data->len++;
}

void	pf_putchar(char c, t_data *data)
{
	write(1, &c, 1);
	data->print_ret++;
}
