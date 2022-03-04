/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:47:02 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/05 01:06:15 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_percent(t_info *info, t_data *data)
{
	if (!(info->flag & MINUS) && !(info->flag & ZERO))
	{
		while (--data->width > 0)
			pf_putchar(' ', data);
		pf_putchar('%', data);
	}
	else if (!(info->flag & MINUS) && (info->flag & ZERO))
	{
		while (--data->width > 0)
			pf_putchar('0', data);
		pf_putchar('%', data);
	}
	else if (info->flag & MINUS)
	{
		pf_putchar('%', data);
		while (--data->width > 0)
			pf_putchar(' ', data);
	}
}

void	print_string(va_list ap, t_info *info, t_data *data)
{
	char	*s;

	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";
	pf_strlen(s, info, data);
	if (data->prec && data->prec < data->len)
		data->margin_space = data->width - data->prec;
	else if ((data->prec >= data->len) || (data->width > data->len))
		data->margin_space = data->width - data->len;
	if (info->flag & MINUS)
	{
		pf_putstr(s, info, data);
		while (data->margin_space-- > 0)
			pf_putchar(' ', data);
	}
	if (!(info->flag & MINUS))
	{
		while (data->margin_space-- > 0 && data->width > data->prec)
			pf_putchar(' ', data);
		pf_putstr(s, info, data);
	}
}

void	print_char(va_list ap, t_info *info, t_data *data)
{
	char	c;

	c = (unsigned char)va_arg(ap, int);
	if (info->flag & MINUS)
	{
		pf_putchar(c, data);
		while (--data->width > 0)
			pf_putchar(' ', data);
	}
	else if (!(info->flag & MINUS))
	{
		while (--data->width > 0)
			pf_putchar(' ', data);
		pf_putchar(c, data);
	}
}
