/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:43 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/03 21:33:39 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialization(t_data *data)
{
	data->type = 0;
	data->minus = 0;
	data->plus = 0;
	data->space = 0;
	data->zero = 0;
	data->hash = 0;
	data->lower = 0;
	data->base = 10;
	data->width = 0;
	data->dot = 0;
	data->prec = 0;
	data->len = 0;
	data->margin_space = 0;
	data->margin_zero = 0;
	data->value = 0;
	data->p_value = 0;
}

void	parse_start(const char *str, va_list ap, t_data *data)
{
	while (*str != 0)
	{
		initialization(data);
		if (*str == '%')
		{
			str++;
			parse_flag(&str, data);
			parse_precision_width(&str, data);
			parse_type(&str, ap, data);
		}
		else
		{
			if (data->print_ret == ERROR)
				break ;
			pf_putchar(*(str)++, data);
		}
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_data	data;

	data.print_ret = 0;
	va_start(ap, str);
	parse_start(str, ap, &data);
	va_end(ap);
	return ((int)data.print_ret);
}
