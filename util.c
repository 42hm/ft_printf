/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:48:00 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/03 17:56:19 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putchar(char c, t_data *data)
{
	write(1, &c, 1);
	data->print_ret++;
	if (data->print_ret > INTMAX)
	{
		data->print_ret = ERROR;
	}
}

void	pf_putstr(char *s, t_data *data)
{
	if (data->prec > 0 && data->len < data->prec)
		data->print_ret += write(1, s, data->len);
	else if (data->prec > 0 && data->len > data->prec)
		data->print_ret += write(1, s, data->prec);
	else if (data->type == POINTER || data->hash == ON)
		data->print_ret += write(1, s, 2);
	else
		data->print_ret += write(1, s, data->len);
}

void	pf_strlen(char *s, t_data *data)
{
	if ((data->dot == ON) && (data->prec == OFF))
		return ;
	while (s[data->len] != 0)
		data->len++;
}

void	pf_intlen(long long num, t_data *data)
{
	if (num < 0)
		num *= -1;
	if (num >= 0 && num < 10)
		data->len = 1;
	else
	{
		while (num != 0)
		{
			num /= data->base;
			data->len++;
		}
	}
}
