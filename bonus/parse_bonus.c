/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:31 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/04 06:12:49 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	parse_type(const char **str, va_list ap, t_info *info, t_data *data)
{
	info->type = **str;
	if (**str == CHAR)
		print_char(ap, info, data);
	else if (**str == STRING)
		print_string(ap, info, data);
	else if (**str == PERCENT)
		print_percent(info, data);
	else if (**str == INTEGER_D || **str == INTEGER_I || **str == UNSIGN \
		|| **str == HEX_CAP || **str == HEX_LOW || **str == POINTER)
		prepare_diuxp(ap, info, data);
	(*str)++;
}

void	parse_precision_width(const char **str, t_info *info, t_data *data)
{
	long long	error;

	while (**str >= '0' && **str <= '9')
		data->width = (data->width * 10) + *((*str)++) - '0';
	if (**str == '.')
	{
		info->dot = ON;
		(*str)++;
		while (**str >= '0' && **str <= '9')
			data->prec = (data->prec * 10) + *((*str)++) - '0';
	}
	error = data->width + data->prec + info->hash + data->print_ret;
	if (error > INTMAX)
		data->print_ret = ERROR;
}

void	parse_flag(const char **str, t_info *info)
{
	while (**str == '#' || **str == '-' || **str == '0' \
		|| **str == ' ' || **str == '+')
	{
		if (**str == '#')
			info->hash = ON;
		else if (**str == '-')
			info->minus = ON;
		else if (**str == '0')
		{
			info->zero = ON;
			if (info->zero == ON && info->minus == ON)
				info->zero = OFF;
		}
		else if (**str == ' ')
			info->space = ON;
		else if (**str == '+')
		{
			info->plus = ON;
			if (info->space == ON)
				info->space = OFF;
		}
		(*str)++;
	}
}
