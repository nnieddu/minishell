NAME				=	minishell

CC					=	gcc
CFLAGS				=	-Wall -Wextra -Werror

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
						srcs/signal \
						srcs/utils

INCS				=	minishell.h

SRCS				=	minishell.c \
						home.c \
						variables.c \
						manage.c \
						lexer.c \
						line.c \
						subline.c \
						token.c \
						parser.c \
						tilde.c \
						edit.c \
						conponent.c \
						detect.c \
						browse.c \
						execute.c \
						builtins.c \
						command.c \
						access.c \
						binaries.c \
						echo.c \
						cd.c \
						pwd.c \
						export.c \
						export_print.c \
						unset.c \
						env.c \
						exit.c \
						array.c \
						lexe.c \
						parse.c \
						type.c \
						others.c \
						list.c \
						error.c \
						set_ret.c \
						signal.c \
						signal_next.c \
						syntax.c

OPATH				=	objs/

OBJS				=	$(SRCS:%.c=$(OPATH)%.o)

all					:	$(NAME)

$(OPATH)%.o			:	%.c $(INCS)
						$(shell mkdir -p objs)
						$(CC) $(CFLAGS) -c $< -o $@

$(NAME)				:	$(OBJS)
						$(MAKE) -C $(DIR_FT)
						$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(DIR_FT) $(LIBS)

clean				:
						$(RM) $(OBJS)
						$(RM) -r minishell.dSYM
						$(RM) -r $(OPATH)
						$(MAKE) $@ -C $(DIR_FT)

fclean				:	clean
						$(RM) srcs/libft/libft.a
						$(RM) $(NAME)

re					:	fclean all

.PHONY				:	all clean fclean re
