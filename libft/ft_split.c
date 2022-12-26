/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpuwar <kpuwar@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:04:40 by kpuwar            #+#    #+#             */
/*   Updated: 2022/11/22 12:13:49 by kpuwar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_ptrs(char *s, char c, int len_str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 1;
	while (i < len_str - 1)
	{
		if (s[i + 1] != c && s[i] == c)
			count++;
		i++;
	}
	return (count);
}

static void	delptrs(char **ptr, size_t len)
{
	while (len--)
		free(ptr[len]);
	free(ptr);
}

static void	fillptrs(char *str, char c, char **ptr, int len_str)
{
	int	end;
	int	start;
	int	i;

	end = 0;
	i = 0;
	while (end < len_str)
	{
		if (str[end] != c)
		{
			start = end;
			while (end < len_str && str[end] != c)
				end++;
			ptr[i] = ft_substr(str, start, end - start);
			if (ptr[i] == NULL)
			{
				delptrs(ptr, i);
				return ;
			}
			i++;
		}
		end++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*str;
	int		len;
	int		len_str;

	str = ft_strtrim(s, &c);
	if (!str)
		return (NULL);
	len_str = ft_strlen(str);
	len = count_ptrs(str, c, len_str);
	ptr = (char **) ft_calloc(len + 1, sizeof(char *));
	if (!ptr)
	{
		free(str);
		return (NULL);
	}
	fillptrs(str, c, ptr, len_str);
	free(str);
	return (ptr);
}
