/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diuxp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:44:33 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/04 09:23:53 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_num(t_info *info, t_data *data)
{
	if (data->value != 0 || data->p_value != 0)
	{
		if (data->value < 0)
			data->value *= -1;
		while (data->value != 0 || data->p_value != 0)
		{
			if (info->type == POINTER)
			{
				data->arr[data->i++] = (NUMARR[data->p_value % info->base]) | \
				info->lower;
				data->p_value = data->p_value / info->base;
			}
			else
			{
				data->arr[data->i++] = (NUMARR[data->value % info->base]) | \
				info->lower;
				data->value = data->value / info->base;
			}
		}
		while (data->i-- > 0)
			pf_putchar(data->arr[data->i], data);
	}
}

void	print_null_zero(t_info *info, t_data *data)
{
	if (info->dot == ON && data->value == 0 && data->prec == 0)
		return ;
	if (data->value == 0 && (info->dot == OFF || data->prec > 0) \
		&& data->p_value == 0)
		pf_putchar('0', data);
}

void	print_diuxp(t_info *info, t_data *data)
{
	while (data->margin_space-- > 0 && info->minus == OFF)
		pf_putchar(' ', data);
	if (info->plus == ON || info->space == ON || data->value < 0)
	{
		if (info->plus == ON && data->value >= 0)
			pf_putchar('+', data);
		else if (info->space == ON && data->value >= 0)
			pf_putchar(' ', data);
		else if (info->base == 10 && data->value < 0)
			pf_putchar('-', data);
	}
	if (info->type == HEX_CAP && info->hash == ON && data->value != 0)
		pf_putstr("0X", info, data);
	else if (info->type == POINTER || (info->hash == ON && data->value != 0))
		pf_putstr("0x", info, data);
	while (data->margin_zero-- > 0)
		pf_putchar('0', data);
	print_null_zero(info, data);
	print_num(info, data);
	if (info->minus == ON)
	{
		while (data->margin_space-- >= 0)
			pf_putchar(' ', data);
	}
}

void	calculate_space_zero(t_info *info, t_data *data)
{
	if ((info->plus == ON || info->space == ON || data->value < 0) \
		&& (data->width > data->len) && info->base == 10)
		data->width -= 1;
	if (data->len > data->width && data->len >= data->prec)
		return ;
	if (data->prec >= data->width && data->prec > data->len)
		data->margin_zero = data->prec - data->len;
	if (data->width > data->prec && data->prec > data->len)
	{
		data->margin_space = data->width - data->prec;
		data->margin_zero = data->prec - data->len;
	}
	if (data->width > data->prec && data->len >= data->prec)
	{
		if ((data->len == 1 && info->dot == ON && data->prec == 0) \
			&& (data->value == 0 && data->p_value == 0))
			data->margin_space = data->width;
		else if (info->zero == ON && info->dot == OFF)
			data->margin_zero = data->width - data->len;
		else
			data->margin_space = data->width - data->len;
	}
}

void	prepare_diuxp(va_list ap, t_info *info, t_data *data)
{
	if (info->type == INTEGER_D || info->type == INTEGER_I)
		data->value = va_arg(ap, int);
	else if (info->type == POINTER)
	{
		info->lower = 32;
		info->base = 16;
		data->width -= 2;
		data->p_value = (unsigned long)va_arg(ap, void *);
	}
	else
	{
		if (info->type == HEX_CAP || info->type == HEX_LOW)
		{
			if (info->type == HEX_LOW)
				info->lower = 32;
			info->base = 16;
		}
		data->value = va_arg(ap, unsigned int);
	}
	pf_intlen(info, data);
	calculate_space_zero(info, data);
	print_diuxp(info, data);
}
