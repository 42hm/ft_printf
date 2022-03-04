/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:43 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/04 06:11:31 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	initialization_info(t_info *info)
{
	info->type = 0;
	info->minus = 0;
	info->plus = 0;
	info->space = 0;
	info->zero = 0;
	info->hash = 0;
	info->lower = 0;
	info->base = 10;
	info->dot = 0;
}

void	initialization_data(t_data *data)
{
	data->i = 0;
	data->width = 0;
	data->prec = 0;
	data->len = 0;
	data->margin_space = 0;
	data->margin_zero = 0;
	data->value = 0;
	data->p_value = 0;
}

void	parse_start(const char *str, va_list ap, t_info *info, t_data *data)
{
	while (*str != 0)
	{
		initialization_info(info);
		initialization_data(data);
		if (*str == '%')
		{
			str++;
			parse_flag(&str, info);
			parse_precision_width(&str, info, data);
			parse_type(&str, ap, info, data);
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
	t_info	info;

	data.print_ret = 0;
	va_start(ap, str);
	parse_start(str, ap, &info, &data);
	va_end(ap);
	return ((int)data.print_ret);
}
