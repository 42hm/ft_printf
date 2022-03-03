/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:31 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/03 17:57:42 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_precision_width(const char **str, t_data *data)
{
	long long	error;

	while (**str >= '0' && **str <= '9')
		data->width = (data->width * 10) + *((*str)++) - '0';
	if (**str == '.')
	{
		data->dot = ON;
		(*str)++;
		while (**str >= '0' && **str <= '9')
			data->prec = (data->prec * 10) + *((*str)++) - '0';
	}
	error = data->width + data->prec + data->hash + data->print_ret;
	if (error > INTMAX)
		data->print_ret = ERROR;
}

void	parse_flag(const char **str, t_data *data)
{
	while (**str == '#' || **str == '-' || **str == '0' \
		|| **str == ' ' || **str == '+')
	{
		if (**str == '#')
			data->hash = ON;
		else if (**str == '-')
			data->minus = ON;
		else if (**str == '0')
		{
			data->zero = ON;
			if (data->zero == ON && data->minus == ON)
				data->zero = OFF;
		}
		else if (**str == ' ')
			data->space = ON;
		else if (**str == '+')
		{
			data->plus = ON;
			if (data->space == ON)
				data->space = OFF;
		}
		(*str)++;
	}
}

void	parse_type(const char **str, va_list ap, t_data *data)
{
	data->type = **str;
	if (**str == CHAR)
		print_char(ap, data);
	else if (**str == STRING)
		print_string(ap, data);
	else if (**str == PERCENT)
		print_percent(data);
	else if (**str == INTEGER_D || **str == INTEGER_I || **str == UNSIGN \
		|| **str == HEX_CAP || **str == HEX_LOW || **str == POINTER)
		prepare_diuxp(ap, data);
	(*str)++;
}
