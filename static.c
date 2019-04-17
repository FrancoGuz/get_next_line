/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 11:49:52 by fguzman           #+#    #+#             */
/*   Updated: 2019/04/16 13:27:58 by fguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	fun(void)
{
	static int count = 0;
	count++;
	return count;
}

int main(void)
{
	
	printf("%d ", fun());
	printf("%d ", fun());
	printf("%d ", fun());
	printf("%d ", fun());
	return (0);
}
