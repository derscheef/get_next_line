/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yscheef <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:46:43 by yscheef           #+#    #+#             */
/*   Updated: 2023/01/23 13:48:09 by yscheef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*reader(int fd, char *text)
{
	int		charsread;
	char	*buffer;

	charsread = 69;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (ft_strchr(text, '\n') == 0 && charsread > 0)
	{
		charsread = read(fd, buffer, BUFFER_SIZE);
		if (charsread == -1)
		{
			free(buffer);
			free(text);
			return (NULL);
		}
		buffer[charsread] = '\0';
		text = ft_strjoin(text, buffer);
	}
	free(buffer);
	return (text);
}

char	*textreturn(char *text)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	if (!text[0])
		return (NULL);
	while (text[i] != '\n' && text[i] != '\0')
		i++;
	if (text[i] == '\n')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	tmp[i] = '\0';
	while (i--)
		tmp[i] = text[i];
	return (tmp);
}

char	*remain(char *text, int i)
{
	char			*tmp;
	unsigned int	counter;

	counter = 0;
	if (!text[i])
	{
		free(text);
		return (NULL);
	}
	if (text[i] == '\n')
		i++;
	while (text[i + counter] != '\0')
		counter++;
	tmp = (char *)malloc(sizeof(char) * (counter + 1));
	if (!tmp)
		return (NULL);
	tmp[counter] = '\0';
	while (counter--)
		tmp[counter] = text[i + counter];
	free(text);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char		*text;
	char			*out;
	unsigned int	i;

	i = 0;
	text = reader(fd, text);
	if (text == NULL)
		return (NULL);
	out = textreturn(text);
	while (text[i] != '\n' && text[i] != '\0')
		i++;
	text = remain(text, i);
	return (out);
}

// int	main(int argc, char const *argv[])
// {
// 	int		fd;
// 	char	*s;

// 	if (argc == 2)
// 		fd = open(argv[1], O_RDONLY);
// 	else
// 		fd = open("text.txt", O_RDONLY);
// 	if (fd < 0)
// 		printf("Error: No file read\n");
// 	s = get_next_line(fd);
// 	while (ft_strlen(s))
// 	{
// 		printf("%s", s);
// 		free(s);
// 		s = get_next_line(fd);
// 		usleep(300000);
// 	}
// 	free(s);
// 	return (0);
// }
