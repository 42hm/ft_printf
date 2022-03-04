/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:43 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/05 08:00:50 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialization(t_info *info, t_data *data)
{
	info->type = 0;
	info->flag = 0;
	info->base = 10;
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
	t_queue	queue;

	initqueue(&queue);
	while (*str != 0)
	{
		initialization(info, data);
		if (*str == '%')
		{
			str++;
			parse_flag(&str, info);
			parse_precision_width(&str, info, data);
			printqueue(&queue, data, info);
			if (data->print_ret == ERROR)
				return ;
			parse_type(&str, ap, info, data);
		}
		else
		{
			enqueue(*(str)++, &queue, data);
			if (data->print_ret == ERROR)
				return ;
		}
	}
	if (!info->type_count || queue.count)
		printqueue(&queue, data, info);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_data	data;
	t_info	info;

	data.print_ret = 0;
	info.type_count = 0;
	va_start(ap, str);
	parse_start(str, ap, &info, &data);
	va_end(ap);
	return (data.print_ret);
}
