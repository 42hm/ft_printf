/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 05:05:10 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/05 07:22:29 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dequeue(t_queue *queue, t_data *data)
{
	t_node	*ptr;

	if (queue->count == 0)
		return ;
	ptr = queue->front;
	pf_putchar(ptr->data, data);
	queue->front = ptr->next;
	free(ptr);
	ptr = NULL;
	queue->count--;
}

void	printqueue(t_queue *queue, t_data *data, t_info *info)
{
	int	forprec;

	forprec = 0;
	if (info->flag & PLUS || info->flag & SPACE)
		forprec = 1;
	if (data->width + queue->count >= INTMAX || \
		data->prec + queue->count + forprec + (info->flag & HASH) >= INTMAX)
	{
		data->print_ret = ERROR;
	}
	else if (queue->count)
	{
		while (queue->count > 0)
			dequeue(queue, data);
		initqueue(queue);
	}
}

void	enqueue(char str, t_queue *queue, t_data *data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		data->print_ret = ERROR;
	node->data = str;
	node->next = NULL;
	if (queue->count == 0)
		queue->front = node;
	else
		queue->rear->next = node;
	queue->rear = node;
	queue->count++;
}

void	initqueue(t_queue *queue)
{
	queue->front = NULL;
	queue->rear = NULL;
	queue->count = 0;
}
