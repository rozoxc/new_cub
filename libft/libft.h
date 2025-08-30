/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:01:39 by selbouka          #+#    #+#             */
/*   Updated: 2025/08/30 10:39:56 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				content;
	int				index;
	struct s_list	*next;
}	t_list;

typedef struct garbage_c
{
	void				*data;
	struct garbage_c	*next;
}	t_collect;

long	ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int n);

t_list	*ft_lstnew(int content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	*ft_malloc(size_t size, int mode);
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strcpy(char *dst, const char *src);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strtrim(char const *s);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);


#endif