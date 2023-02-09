/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:00:30 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 15:49:42 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(void)
// {
// 	char	*x;

// 	x = "100";
// 	printf("%ld\n", ft_atoi(x));
// 	readline(x);
// }

// int	readline(char *location)
// {
// 	FILE	*ostream;
// 	char	result;
// 	int		count;

// 	ostream = fopen(location, "r");
// 	if (ostream == NULL)
// 	{
// 		return (0);
// 	}
// 	count = 0;
// 	result = getc(ostream);
// 	while (result != 10)
// 	{
// 		printf("%c",result);
// 		result = getc(ostream);
// 		count++;
// 	}
// 	printf("\n");
// 	return (count);
// }

int	main(void) 
{
	int fd = open("test.txt", O_RDONLY);
	char *test = malloc(sizeof(char) * 999);
	
	int len = read(fd, test, 999);
	printf("%s\n", readline(test));
	free(test);
}
