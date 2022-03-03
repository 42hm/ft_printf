/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diuxp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:44:33 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/03 21:36:03 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_diuxp(t_data *data)
{
	char	arr[21];
	int		index;

	index = 0;
	if (data->dot == ON && data->value == 0 && data->prec == 0)
		return ;
	if (data->value == 0 && (data->dot == OFF || data->prec > 0) \
		&& data->p_value == 0)
		pf_putchar('0', data);
	else if (data->value != 0 || data->p_value != 0)
	{
		if (data->value < 0)
			data->value *= -1;
		while (data->value != 0 || data->p_value != 0)
		{
			if (data->type == POINTER)
			{
				arr[index++] = (NUMARR[data->p_value % data->base]) | data->lower;
				data->p_value = data->p_value / data->base;
			}
			else
			{
				arr[index++] = (NUMARR[data->value % data->base]) | data->lower;
				data->value = data->value / data->base;
			}
		}
		while (index-- > 0)
			pf_putchar(arr[index], data);
	}
}

void	if_minus_off(t_data *data)
{
	if (data->minus == OFF)
	{
		while (data->margin_space-- > 0)
			pf_putchar(' ', data);
		if (data->plus == ON || data->value < 0 || data->space == ON)
		{
			if (data->plus == ON && data->value >= 0)
				pf_putchar('+', data);
			else if (data->space == ON && data->value >= 0)
				pf_putchar(' ', data);
			else if (data->value < 0 && data->base == 10)
				pf_putchar('-', data);
		}
		if (data->type == HEX_CAP && (data->hash == ON && data->value != 0))
			pf_putstr("0X", data);
		else if (data->type == POINTER || \
			(data->hash == ON && data->value != 0))
			pf_putstr("0x", data);
		while (data->margin_zero-- > 0)
			pf_putchar('0', data);
		print_diuxp(data);
	}
}

void	if_minus_on(t_data *data)
{
	if (data->minus == ON)
	{
		if (data->plus == ON || data->value < 0 || data->space == ON)
		{
			if (data->plus == ON && data->value >= 0)
				pf_putchar('+', data);
			else if (data->space == ON && data->value >= 0)
				pf_putchar(' ', data);
			else if (data->value < 0 && data->base == 10)
				pf_putchar('-', data);
		}
		if (data->type == HEX_CAP && data->value > 0 && data->hash == ON)
			pf_putstr("0X", data);
		else if (data->type == POINTER || data->hash == ON)
			pf_putstr("0x", data);
		while (data->margin_zero-- > 0)
			pf_putchar('0', data);
		print_diuxp(data);
		while (data->margin_space-- > 0)
			pf_putchar(' ', data);
	}
}

void	calculate_space_zero(t_data *data)
{
	if ((data->plus == ON || data->space == ON || data->value < 0) \
		&& (data->width > data->len) && data->base == 10)
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
		if ((data->len == 1 && data->dot == ON && data->prec == 0) \
			&& (data->value == 0 && data->p_value == 0))
			data->margin_space = data->width;
		else if (data->zero == ON && data->dot == OFF)
			data->margin_zero = data->width - data->len;
		else
			data->margin_space = data->width - data->len;
	}
}

void	prepare_diuxp(va_list ap, t_data *data)
{
	if (data->type == INTEGER_D || data->type == INTEGER_I)
		data->value = va_arg(ap, int);
	else if (data->type == POINTER)
	{
		data->lower = 32;
		data->base = 16;
		data->width -= 2;
		data->p_value = (unsigned long)va_arg(ap, void *);
	}
	else
	{
		if (data->type == HEX_CAP || data->type == HEX_LOW)
		{
			if (data->type == HEX_LOW)
				data->lower = 32;
			data->base = 16;
		}
		data->value = va_arg(ap, unsigned int);
	}
	pf_intlen(data);
	calculate_space_zero(data);
	if_minus_on(data);
	if_minus_off(data);
}
