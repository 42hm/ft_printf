/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diuxp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:44:33 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/03 18:22:14 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_diuxp(long long num, t_data *data)
{
	char	arr[21];
	int		index;

	index = 0;
	if (data->dot == ON && num == 0 && data->prec == 0)
		return ;
	if (num == 0 && (data->dot == OFF || data->prec > 0))
		pf_putchar('0', data);
	else if (num != 0)
	{
		if (num < 0 && (!(data->type == POINTER && num == -1)))
			num *= -1;
		while (num != 0)
		{
			arr[index++] = (NUMARR[num % data->base]) | data->lower;
			num = num / data->base;
		}
		while (index-- > 0)
			pf_putchar(arr[index], data);
	}
}

void	if_minus_off(long long num, t_data *data)
{
	if (data->minus == OFF)
	{
		while (data->margin_space-- > 0)
			pf_putchar(' ', data);
		if (data->plus == ON || num < 0 || data->space == ON)
		{
			if (data->plus == ON && num >= 0)
				pf_putchar('+', data);
			else if (data->space == ON && num >= 0)
				pf_putchar(' ', data);
			else if (num < 0 && data->base == 10)
				pf_putchar('-', data);
		}
		if (data->type == HEX_CAP && (data->hash == ON && num != 0))
			pf_putstr("0X", data);
		else if (data->type == POINTER || (data->hash == ON && num != 0))
			pf_putstr("0x", data);
		while (data->margin_zero-- > 0)
			pf_putchar('0', data);
		print_diuxp(num, data);
	}
}

void	if_minus_on(long long num, t_data *data)
{
	if (data->minus == ON)
	{
		if (data->plus == ON || num < 0 || data->space == ON)
		{
			if (data->plus == ON && num >= 0)
				pf_putchar('+', data);
			else if (data->space == ON && num >= 0)
				pf_putchar(' ', data);
			else if (num < 0 && data->base == 10)
				pf_putchar('-', data);
		}
		if (data->type == HEX_CAP && num > 0 && data->hash == ON)
			pf_putstr("0X", data);
		else if (data->type == POINTER || data->hash == ON)
			pf_putstr("0x", data);
		while (data->margin_zero-- > 0)
			pf_putchar('0', data);
		print_diuxp(num, data);
		while (data->margin_space-- > 0)
			pf_putchar(' ', data);
	}
}

void	calculate_space_zero(long long num, t_data *data)
{
	if ((data->plus == ON || data->space == ON || num < 0) \
		&& (data->width > data->len) && data->base == 10)
		data->width -= 1;
	if (data->len > data->width && data->len >= data->prec)
		return ;
	if (data->prec >= data->width && (data->prec > data->len))
		data->margin_zero = data->prec - data->len;
	if (data->width > data->prec && (data->prec > data->len))
	{
		data->margin_space = data->width - data->prec;
		data->margin_zero = data->prec - data->len;
	}
	if (data->width > data->prec && data->len >= data->prec)
	{
		if (data->len == 1 && data->dot == ON && data->prec == 0 && num == 0)
			data->margin_space = data->width;
		else if (data->zero == ON && data->dot == OFF)
			data->margin_zero = data->width - data->len;
		else
			data->margin_space = data->width - data->len;
	}
}

void	prepare_diuxp(va_list ap, t_data *data)
{
	long long	num;

	if (data->type == INTEGER_D || data->type == INTEGER_I)
		num = va_arg(ap, int);
	else if (data->type == POINTER)
	{
		data->lower = 32;
		data->base = 16;
		data->width -= 2;
		num = (unsigned long)va_arg(ap, void *);
	}
	else
	{
		if (data->type == HEX_CAP || data->type == HEX_LOW)
		{
			if (data->type == HEX_LOW)
				data->lower = 32;
			data->base = 16;
		}
		num = va_arg(ap, unsigned int);
	}
	pf_intlen(num, data);
	calculate_space_zero(num, data);
	if_minus_on(num, data);
	if_minus_off(num, data);
}
