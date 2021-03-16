/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_update.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:47:28 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/02 08:40:34 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UPDATE_H
# define LIBFT_UPDATE_H

# include <stdlib.h>
# include <unistd.h>

void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_ischarset(int c, const char *s);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		ft_putnbr_fd(int n, int fd);
void		ft_putnbr_base(const char *base, int n, int signe);
void		ft_putchar(char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr(char const *s);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putendl(char *s);
int			ft_nbrlen(int n);
int			ft_nbrlen_base(const char *base, int n, int signe);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
size_t		ft_strlen(const char *s);
size_t		ft_strlen_chr(const char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strcmp_chr(const char *s1, const char *s2, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strcpy(char *s1, const char *s2);
char		*ft_strncpy(char *s1, const char *s2, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strnew(size_t size);
void		ft_strclr(char *s);
void		ft_strdel(char **as);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strdup(const char *s1);
char		*ft_strdup_chr(const char *s1, int c);
char		*ft_strdup_idx(const char *s1, int c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_chr(char const *s1, int c, char const *s2, int d);
char		*ft_strjoin_idx(char const *s1, char const *s2, int ind);
char		**ft_split(char const *s, char c);
char		**ft_split_charset(char const *s, char const *set);
void		ft_tabnbrdel(int ***tab, int size);
int			ft_tabstrlen(char **tab);
void		ft_tabstrclr(char **tab);
void		ft_tabstrdel(char ***tab);
int			get_next_line(int fd, char **line);
int			get_next_line_fd(int fd, char **line);

#endif
