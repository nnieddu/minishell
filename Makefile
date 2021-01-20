NAME				=	minishell

CC					=	gcc
CFLAGS				=	-Wall -Wextra -Werror -g

DIR_FT				=	srcs/libft/
LIBS				=	-lft

VPATH				=	incs/ \
						srcs/ \
						srcs/environment \
						srcs/lexing \
						srcs/parsing \
						srcs/redirection \
						srcs/builtins \
						srcs/execution \
						srcs/signaux \
						srcs/utils

INCS				=	minishell.h

SRCS				=	minishell.c \
						manage.c \
						lexer.c \
						line.c \
						subline.c \
						token.c \
						parser.c \
						expand.c \
						edit.c \
						conponent.c \
						detect.c \
						browse.c \
						executer.c \
						builtins.c \
						command.c \
						binaries.c \
						echo.c \
						cd.c \
						pwd.c \
						export.c \
						unset.c \
						env.c \
						exit.c \
						array.c \
						is.c \
						list.c \
						error.c \
						set_ret.c\
						signal.c\
						signal_next.c\
						crash.c

OPATH				=	objs/

OBJS				=	$(SRCS:%.c=$(OPATH)%.o)

all					:	$(NAME)

$(OPATH)%.o			:	%.c $(INCS)
						$(shell mkdir -p objs)
						$(CC) $(CFLAGS) -c $< -o $@

$(NAME)				:	$(OBJS)
						$(MAKE) -C $(DIR_FT)
						$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(DIR_FT) $(LIBS)

# --trace-children=yes

clean				:
						$(RM) $(OBJS)
						$(RM) -r $(OPATH)
						$(MAKE) $@ -C $(DIR_FT)

fclean				:	clean
						$(RM) srcs/libft/libft.a
						$(RM) $(NAME)

re					:	fclean all

.PHONY				:	all clean fclean re
