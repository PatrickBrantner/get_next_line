/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrantne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:27:17 by pbrantne          #+#    #+#             */
/*   Updated: 2022/11/14 13:32:27 by pbrantne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "get_next_line.h"

char	*free_dict(char *dict1, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(dict1, buffer);
	free(dict1);
	return (temp);
}

char	*return_line(char *dict)
{
	char	*output_dict;
	int		i;

	i = 0;
	if (dict[i] == '\0')
		return (NULL);
	while (dict[i] != '\n' && dict[i] != '\0')
		i++;
	output_dict = ft_calloc(i + 2, sizeof(char));
	if (!output_dict)
	{
		free (output_dict);
		return (NULL);
	}
	i = 0;
	while (dict[i] != '\n' && dict[i] != '\0')
	{	
		output_dict[i] = dict[i];
		i++;
	}
	if (dict[i] == '\n')
		output_dict[i++] = '\n';
	output_dict[i] = '\0';
	return (output_dict);
}

char	*set_to_next(char *swap, int i)
{
	char	*new_beginning;
	int		j;

	j = 0;
	if (!swap[i])
	{
		free (swap);
		return (NULL);
	}
	new_beginning = ft_calloc(ft_strlen(swap) - i + 1, sizeof(char));
	if (!new_beginning)
	{
		free(new_beginning);
		return (NULL);
	}
	while (swap[i] != '\0')
		new_beginning[j++] = swap[i++];
	new_beginning[j] = '\0';
	free (swap);
	return (new_beginning);
}

char	*read_data(int fd, char *dict)
{
	char	*buffer;
	int		ch_read;

	if (!dict)
		dict = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	ch_read = 1;
	while (ch_read > 0)
	{
		ch_read = read(fd, buffer, BUFFER_SIZE);
		if (ch_read == -1)
		{	
			free(buffer);
			return (NULL);
		}
		buffer[ch_read] = '\0';
		dict = free_dict(dict, buffer);
		if (ft_strchr(dict, '\n'))
		{
			free (buffer);
			return (dict);
		}
	}
	free(buffer);
	return (dict);
}

char	*get_next_line(int fd)
{
	static char	*dict;
	char		*ret;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free (dict);
		dict = NULL;
		return (NULL);
	}
	dict = read_data(fd, dict);
	if (dict[0] == '\0')
	{
		free (dict);
		dict = NULL;
		return (NULL);
	}
	ret = return_line(dict);
	i = ft_strlen(ret);
	dict = set_to_next(dict, i);
	return (ret);
}

/* int main()
{
	char *str;

	str = get_next_line(0);
	printf("\n%s", str);
} */