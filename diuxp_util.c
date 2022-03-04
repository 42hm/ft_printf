/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diuxp_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:48:00 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/05 00:54:13 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_intlen(t_info *info, t_data *data)
{
	long long		temp;
	unsigned long	p_temp;

	temp = data->value;
	p_temp = data->p_value;
	if (temp < 0)
		temp *= -1;
	if ((temp >= 0 && temp < 10) && (p_temp >= 0 && p_temp < 10))
		data->len = 1;
	else if (info->type == POINTER)
	{
		while (p_temp != 0)
		{
			p_temp /= info->base;
			data->len++;
		}
	}
	else
	{
		while (temp != 0)
		{
			temp /= info->base;
			data->len++;
		}
	}
}
