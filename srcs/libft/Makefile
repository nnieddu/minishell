# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/05 20:31:38 by jobenass          #+#    #+#              #
#    Updated: 2020/12/16 15:15:03 by jobenass         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME				=	libft.a

CC					= 	gcc
CFLAGS				= 	-Wall -Wextra -Werror
AR					=	ar rc

INCS				=	libft_update.h get_next_line.h

SRCS				=	ft_memset.c \
						ft_bzero.c \
						ft_memcpy.c \
						ft_memccpy.c \
						ft_memmove.c \
						ft_memchr.c \
						ft_memcmp.c \
						ft_isalpha.c \
						ft_isdigit.c \
						ft_isalnum.c \
						ft_isascii.c \
						ft_isprint.c \
						ft_isspace.c \
						ft_ischarset.c \
						ft_toupper.c \
						ft_tolower.c \
						ft_putnbr_fd.c \
						ft_putnbr_base.c \
						ft_putchar.c \
						ft_putchar_fd.c \
						ft_putstr.c \
						ft_putstr_fd.c \
						ft_putendl_fd.c \
						ft_putendl.c \
						ft_nbrlen.c \
						ft_nbrlen_base.c \
						ft_atoi.c \
						ft_itoa.c \
						ft_strlen.c \
						ft_strlen_chr.c\
						ft_strchr.c \
						ft_strrchr.c \
						ft_strcmp.c \
						ft_strcmp_chr.c \
						ft_strncmp.c \
						ft_strcpy.c \
						ft_strncpy.c \
						ft_strlcpy.c \
						ft_strcat.c \
						ft_strncat.c \
						ft_strlcat.c \
						ft_strnstr.c \
						ft_calloc.c \
						ft_strnew.c \
						ft_strclr.c \
						ft_strdel.c \
						ft_substr.c \
						ft_strtrim.c \
						ft_strmapi.c \
						ft_strdup.c \
						ft_strdup_chr.c \
						ft_strdup_idx.c \
						ft_strjoin.c \
						ft_strjoin_chr.c \
						ft_strjoin_idx.c \
						ft_split.c \
						ft_split_charset.c \
						ft_tabstrlen.c \
						ft_tabstrclr.c \
						ft_tabstrdel.c \
						ft_tabnbrdel.c \
						get_next_line.c \
						get_next_line_bonus.c \
						get_next_line_utils_bonus.c

OPATH				=	objs/

OBJS				=	$(SRCS:%.c=$(OPATH)%.o)

all					:	$(NAME)

$(OPATH)%.o			:	%.c $(INCS)
						$(shell mkdir -p objs)
						$(CC) $(CFLAGS) -c $< -o $@

$(NAME)				:	$(OBJS)
						$(AR) $(NAME) $(OBJS)

clean				:
						$(RM) $(OBJS)
						$(RM) -r $(OPATH)

fclean				:	clean
						$(RM) $(NAME)

re					:	fclean all

.PHONY				:	all clean fclean re
