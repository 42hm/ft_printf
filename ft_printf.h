/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:41:58 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/04 00:45:53 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define NUMARR "0123456789ABCDEF"
# define INTMAX 2147483647

# define ON 2
# define OFF 0
# define ERROR -1

# define CHAR 99
# define STRING 115
# define UNSIGN 117
# define INTEGER_D 100
# define INTEGER_I 105
# define POINTER 112
# define HEX_LOW 120
# define HEX_CAP 88
# define PERCENT 37

typedef struct s_info
{
	int				type;
	int				minus;
	int				plus;
	int				space;
	int				zero;
	int				lower;
	int				hash;
	int				base;
	int				dot;
}					t_info;

typedef struct s_data
{
	int				i;
	char			arr[21];
	long long		width;
	long long		prec;
	long long		len;
	long long		margin_space;
	long long		margin_zero;
	long long		print_ret;
	long long		value;
	unsigned long	p_value;
}					t_data;

void	print_percent(t_info *info, t_data *data);
void	print_char(va_list ap, t_info *info, t_data *data);
void	print_string(va_list ap, t_info *info, t_data *data);
void	pf_intlen(t_info *info, t_data *data);
void	pf_putchar(char c, t_data *data);
void	pf_putstr(char *s, t_info *info, t_data *data);
void	pf_strlen(char *s, t_info *info, t_data *data);
void	print_null_zero(t_info *info, t_data *data);
void	calculate_space_zero(t_info *info, t_data *data);
void	print_num(t_info *info, t_data *data);
void	print_diuxp(t_info *info, t_data *data);
void	prepare_diuxp(va_list ap, t_info *info, t_data *data);
void	parse_precision_width(const char **str, t_info *info, t_data *data);
void	parse_flag(const char **str, t_info *info);
void	parse_type(const char **str, va_list ap, t_info *info, t_data *data);
void	initialization_info(t_info *info);
void	initialization_data(t_data *data);
void	parse_start(const char *str, va_list ap, t_info *info, t_data *data);
int		ft_printf(const char *str, ...);

#endif
