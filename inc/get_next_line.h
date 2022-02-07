/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:55:18 by rschleic          #+#    #+#             */
/*   Updated: 2021/09/14 14:28:49 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
int		search(char *s, char c);
char	*output_function(char	**pot, ssize_t bytes);
char	*output_extension(char	**pot);
size_t	my_strlen(size_t start, char *str);
void	*my_calloc(size_t count, size_t size);
char	*my_strjoin(char	*s1, char	*s2);
char	*my_substr(char	*s, unsigned	int start, size_t len);
void	my_free(char **ptr);

#endif