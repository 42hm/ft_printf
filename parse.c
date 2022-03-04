/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:31 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/05 06:45:25 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	while (**str >= '0' && **str <= '9')
		data->width = (data->width * 10) + *((*str)++) - '0';
	if (**str == '.')
	{
		info->flag |= DOT;
		(*str)++;
		while (**str >= '0' && **str <= '9')
			data->prec = (data->prec * 10) + *((*str)++) - '0';
	}
}

void	parse_flag(const char **str, t_info *info)
{
	while (**str == '#' || **str == '-' || **str == '0' \
		|| **str == ' ' || **str == '+')
	{
		if (**str == '#')
			info->flag |= HASH;
		else if (**str == '-')
			info->flag |= MINUS;
		else if (**str == '0')
		{
			info->flag |= ZERO;
			if ((info->flag & ZERO) && (info->flag & MINUS))
				info->flag &= ~ZERO;
		}
		else if (**str == ' ')
			info->flag |= SPACE;
		else if (**str == '+')
		{
			info->flag |= PLUS;
			if (info->flag & SPACE)
				info->flag &= ~SPACE;
		}
		(*str)++;
	}
}
