/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:48:00 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/04 09:24:57 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_intlen(t_info *info, t_data *data)
{
	long long		temp;
	unsigned long	p_temp;

	temp = data->value;
	p_temp = data->p_value;
	if (temp < 0)
		temp *= -1;
	if ((temp >= 0 && temp < 10) && (p_temp >= 0 && p_temp < 10))
		data->len = 1;
	else if (info->type == POINTER)
	{
		while (p_temp != 0)
		{
			p_temp /= info->base;
			data->len++;
		}
	}
	else
	{
		while (temp != 0)
		{
			temp /= info->base;
			data->len++;
		}
	}
}

void	pf_putstr(char *s, t_info *info, t_data *data)
{
	if (data->prec > 0 && data->len < data->prec)
		data->print_ret += write(1, s, data->len);
	else if (data->prec > 0 && data->len > data->prec)
		data->print_ret += write(1, s, data->prec);
	else if (info->type == POINTER || info->hash == ON)
		data->print_ret += write(1, s, 2);
	else
		data->print_ret += write(1, s, data->len);
}

void	pf_strlen(char *s, t_info *info, t_data *data)
{
	if ((info->dot == ON) && (data->prec == OFF))
		return ;
	while (s[data->len] != 0)
		data->len++;
}

void	pf_putchar(char c, t_data *data)
{
	write(1, &c, 1);
	data->print_ret++;
	if (data->print_ret > INTMAX)
	{
		data->print_ret = ERROR;
	}
}
